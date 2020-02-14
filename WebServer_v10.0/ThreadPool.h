//
// Created by yongpu on 2/12/20.
//

#ifndef WEBSERVER_10_0_THREADPOOL_H
#define WEBSERVER_10_0_THREADPOOL_H

#include "Channel.h"
#include <pthread.h>
#include <functional>
#include <memory>
#include <vector>

const int THREADPOOL_INVALID = -1;
const int THREADPOOL_LOCK_FAILURE = -2;
const int THREADPOOL_QUEUE_FULL = -3;
const int THREADPOOL_SHUTDOWN = -4;
const int THREADPOOL_THREAD_FAILURE = -5;
const int THREADPOOL_GRACEFUL = 1;

const int MAX_THREADS = 1024;
const int MAX_QUEUE = 65535;

// 关闭的方式，直接/优雅关闭
typedef enum {
    immediate_shutdown = 1,
    graceful_shutdown = 2
} ShutDownOption;

// 任务队列结构
struct ThreadPoolTask {
    std::function<void(std::shared_ptr<void>)> fun; // 回调函数
    std::shared_ptr<void> args; // 参数
};


class ThreadPool {
private:
    static pthread_mutex_t lock;    // 线程池同步锁
    static pthread_cond_t notify;   // 线程等待的条件变量

    static std::vector<pthread_t> threads;  // 线程vector
    static std::vector<ThreadPoolTask> queue;   // 任务队列
    static int thread_count;        // 线程数量

    static int queue_size;          // 队列大小
    static int head;                // 任务队列头
    static int tail;                // 任务队列尾，tail 指向尾节点的下一节点
    static int count;               // 任务队列

    static int shutdown;
    static int started;
public:
    // 创建线程池
    static int threadpool_create(int _thread_count, int _queue_size);

    // 向队列中增加任务
    static int threadpool_add(std::shared_ptr<void> args, std::function<void(std::shared_ptr<void>)> fun);

    // 销毁线程池
    static int threadpool_destroy(ShutDownOption shutdown_option = graceful_shutdown);

    // 释放线程池
    static int threadpool_free();

    // 线程池线程工作函数
    static void *threadpool_thread(void *args);
};


#endif //WEBSERVER_10_0_THREADPOOL_H
