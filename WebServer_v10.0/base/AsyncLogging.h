#pragma once

#include "CountDownLatch.h"
#include "MutexLock.h"
#include "Thread.h"
#include "LogStream.h"
#include "noncopyable.h"
#include <functional>
#include <string>
#include <vector>

class AsyncLogging : noncopyable {
public:
    AsyncLogging(const std::string basename, int flushInterval = 2);

    ~AsyncLogging() {
        if (running_)
            stop();
    }

    void append(const char *logline, int len);

    // 日志系统开始
    void start() {
        running_ = true;
        // 在构造函数中latch_的值为1
        thread_.start();    // 线程开始
        latch_.wait();      // 必须等到latch_变为0才能从start函数中返回，这表明初始化已经完成，等待日志线程启动
    }

    // 日志系统停止
    void stop() {
        running_ = false;
        cond_.notify();
        thread_.join();     // 结束线程
    }


private:
    void threadFunc();      // 线程工作函数
    typedef FixedBuffer<kLargeBuffer> Buffer;
    typedef std::vector<std::shared_ptr<Buffer>> BufferVector;
    typedef std::shared_ptr<Buffer> BufferPtr;
    const int flushInterval_;
    bool running_;
    std::string basename_;
    Thread thread_;             // 执行该异步日志记录器的线程
    MutexLock mutex_;
    Condition cond_;
    BufferPtr currentBuffer_;
    BufferPtr nextBuffer_;      // 预备缓冲区
    BufferVector buffers_;      // 缓冲区队列，待写入文件
    CountDownLatch latch_;      // 倒数计数，用于指示什么时候日志记录器才能开始正常工作,用于等待线程启动
};