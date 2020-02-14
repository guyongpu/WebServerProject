#include "AsyncLogging.h"
#include "LogFile.h"
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <functional>


AsyncLogging::AsyncLogging(std::string logFileName_, int flushInterval)
        : flushInterval_(flushInterval),
          running_(false),
          basename_(logFileName_),
          thread_(std::bind(&AsyncLogging::threadFunc, this), "Logging"),
          mutex_(),
          cond_(mutex_),
          currentBuffer_(new Buffer),
          nextBuffer_(new Buffer),
          buffers_(),
          latch_(1) {
    assert(logFileName_.size() > 1);
    currentBuffer_->bzero();
    nextBuffer_->bzero();
    buffers_.reserve(16);
}

// 前端部分
// 所有LOG_*最终都会调用append函数
// 前台线程所做的工作比较简单，如果currentBuffer_够用，就把日志内容写入到currentBuffer_中，如果不够用(就认为其满了)，
// 就把currentBuffer_放到已满buffer数组中，等待消费者线程（即后台线程）来取。并且把currentBuffer_指向nextBuffer_的buffer。
void AsyncLogging::append(const char *logline, int len) {
    MutexLockGuard lock(mutex_);            /* 将logline写入到文件中 */
    if (currentBuffer_->avail() > len)          /* 当前buffer容量能够写入logline */
        currentBuffer_->append(logline, len);   /* 将logline写入到文件中 */
    else {
        buffers_.push_back(currentBuffer_);     /* 将当前buffer存入到buffers中 */
        currentBuffer_.reset();                 /* 智能指针计数器减1 */
        if (nextBuffer_) {
            //std::move是将对象的状态或者所有权从一个对象转移到另一个对象，只是转移，没有内存的搬迁或者内存拷贝
            currentBuffer_ = std::move(nextBuffer_);    /* 将nextBuffer的空间给currentBuffer */
        } else {
            // 通过reset方法重置指向另一个对象，此时原对象的引用计数减一
            currentBuffer_.reset(new Buffer);
        }

        currentBuffer_->append(logline, len);
        cond_.notify();  // 通知日志线程，有数据可写,也就是说，只有当缓冲区满了之后才会将数据写入日志文件中
    }
}

// 后端部分
// 线程调用的函数，主要用于周期性的flush数据到日志文件中
// 先用线程同步中的条件变量进行睡眠，睡眠时间为日志库的flush时间。
// 所以，当条件变量的条件满足（即前台线程把一个已经满了的buffer放到了buffers_中），或者超时。
// 无论是哪种情况，都还会有一个currentBuffer_前台buffer正在使用。将这个currentBuffer_放到已满buffers_数组中。
// 这样buffers_就有了待进行IO的buffer了。
// 将bufferToWrite和buffers_进行swap。这就完成了将写了日志记录的buffer从前台线程到后台线程的转变。
// 后台线程慢慢进行IO即可
void AsyncLogging::threadFunc() {
    assert(running_ == true);
    latch_.countDown();
    LogFile output(basename_);
    BufferPtr newBuffer1(new Buffer);   // 这两个是后台线程的buffer
    BufferPtr newBuffer2(new Buffer);
    newBuffer1->bzero();
    newBuffer2->bzero();
    BufferVector buffersToWrite;            //用来和前台线程的buffers_进行swap.
    buffersToWrite.reserve(16);
    while (running_) {
        assert(newBuffer1 && newBuffer1->length() == 0);
        assert(newBuffer2 && newBuffer2->length() == 0);
        assert(buffersToWrite.empty());

        {
            // 加锁
            MutexLockGuard lock(mutex_);
            // 如果buffer为空，那么表示没有数据需要写入文件，那么就等待指定的时间（注意这里没有用倒数计数器）
            if (buffers_.empty())  // unusual usage!
            {
                cond_.waitForSeconds(flushInterval_);
            }
            //无论cond是因何而醒来，都要将currentBuffer_放到buffers_中。
            //如果是因为时间到而醒，那么currentBuffer_还没满，此时也要将之写入LogFile中。
            //如果已经有一个前台buffer满了，那么在前台线程中就已经把一个前台buffer放到buffers_中
            //了。此时，还是需要把currentBuffer_放到buffers_中（注意，前后放置是不同的buffer，
            //因为在前台线程中，currentBuffer_已经被换成nextBuffer_指向的buffer了）

            buffers_.push_back(currentBuffer_);
            currentBuffer_.reset(); // 指针计数器减1

            currentBuffer_ = std::move(newBuffer1);
            buffersToWrite.swap(buffers_); // 交换内存
            if (!nextBuffer_) {
                nextBuffer_ = std::move(newBuffer2);
            }
        }

        assert(!buffersToWrite.empty());

        // 如果将要写入文件的buffer列表中buffer的个数大于25，那么将多余数据删除
        // 消息堆积
        //前端陷入死循环，拼命发送日志消息，超过后端的处理能力
        //这是典型的生产速度超过消费速度，会造成数据在内存中的堆积
        //严重时引发性能问题(可用内存不足),
        //或程序崩溃(分配内存失败)
        if (buffersToWrite.size() > 25) {
            //char buf[256];
            // snprintf(buf, sizeof buf, "Dropped log messages at %s, %zd larger buffers\n",
            //          Timestamp::now().toFormattedString().c_str(),
            //          buffersToWrite.size()-2);
            //fputs(buf, stderr);
            //output.append(buf, static_cast<int>(strlen(buf)));
            buffersToWrite.erase(buffersToWrite.begin() + 2, buffersToWrite.end());
        }

        for (size_t i = 0; i < buffersToWrite.size(); ++i) {
            // FIXME: use unbuffered stdio FILE ? or use ::writev ?
            output.append(buffersToWrite[i]->data(), buffersToWrite[i]->length());
        }

        if (buffersToWrite.size() > 2) {
            // drop non-bzero-ed buffers, avoid trashing
            buffersToWrite.resize(2);
        }

        if (!newBuffer1) {
            assert(!buffersToWrite.empty());
            newBuffer1 = buffersToWrite.back();
            buffersToWrite.pop_back();
            newBuffer1->reset();
        }

        if (!newBuffer2) {
            assert(!buffersToWrite.empty());
            newBuffer2 = buffersToWrite.back();
            buffersToWrite.pop_back();
            newBuffer2->reset();
        }

        buffersToWrite.clear();
        output.flush();
    }
    output.flush();
}
