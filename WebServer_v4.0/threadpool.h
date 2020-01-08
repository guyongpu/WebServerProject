//
// Created by yongpu on 2020/1/7.
//

#ifndef WEBSERVER_V2_0_THREADPOOL_H
#define WEBSERVER_V2_0_THREADPOOL_H

#include "requestData.h"
#include <pthread.h>

const int THREADPOOL_INVALID = -1;
const int THREADPOOL_LOCK_FAILURE = -2;
const int THREADPOOL_QUEUE_FULL = -3;
const int THREADPOOL_SHUTDOWN = -4;
const int THREADPOOL_THREAD_FAILURE = -5;
const int THREADPOOL_GRACEFUL = 1;

const int MAX_THREADS = 1024;
const int MAX_QUEUE = 65535;

typedef enum {
    immediate_shutdown = 1,     // 直接关闭
    graceful_shutdown = 2      // 优雅关闭
} threadpool_shutdown_t;

typedef struct {
    void (*function)(void *);   // 回调函数
    void *argument;             // 参数
} threadpool_task_t;

class threadpool;

int threadpool_add(threadpool *pool, void (*function)(void *), void *argument, int flags);

class threadpool {
public:
    threadpool(int thread_count, int queue_size, int flags);

    ~threadpool();

    int threadpool_add(void (*function)(void *), void *argument, int flags);

    int threadpool_destroy(int flags);

    static void *threadpool_thread(void *threadpool);


public:
    pthread_mutex_t lock;
    pthread_cond_t notify;
    pthread_t *threads;
    threadpool_task_t *queue;
    int thread_count;
    int queue_size;
    int head;
    int tail;
    int count;
    int shutdown;
    int started;
};


#endif //WEBSERVER_V2_0_THREADPOOL_H
