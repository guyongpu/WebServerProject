//
// Created by yongpu on 2020/1/7.
//

#include "threadpool.h"

/*构造函数*/
threadpool::threadpool(int thread_count, int queue_size, int flags) {
    do {
        if (thread_count <= 0 || thread_count > MAX_THREADS || queue_size <= 0 || queue_size > MAX_QUEUE) {
            perror("threadpool_create error!");
            return;
        }

        /* 初始化 */
        this->thread_count = 0;
        this->queue_size = queue_size;
        this->head = this->tail = this->count = 0;
        this->shutdown = this->started = 0;

        /*为线程和任务队列分配空间*/
        /*pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * thread_count);*/
        this->threads = new pthread_t[thread_count];
        /*pool->queue = (threadpool_task_t *)malloc(sizeof(threadpool_task_t) * queue_size);*/
        this->queue = new threadpool_task_t[queue_size];

        /*初始化信号量和条件变量*/
        if ((pthread_mutex_init(&(this->lock), NULL) != 0) || (pthread_cond_init(&(this->notify), NULL) != 0)) {
            break;
        }

        /*开始创建工作线程*/
        for (int i = 0; i < thread_count; i++) {
            if (pthread_create(&(this->threads[i]), NULL, this->threadpool_thread, (void *) this) != 0) {
                threadpool_destroy(0);  /*销毁线程池*/
                return;
            }
            this->thread_count++;
            this->started++;
        }
        /*创建成功，返回*/
        return;
    } while (false);

    perror("thread_pool create error!");
    return;
}

/*释放堆上变量*/
threadpool::~threadpool() {
    if (this->threads) {
        delete[] this->threads;
    }
    if (this->queue) {
        delete[] this->queue;
    }
    pthread_mutex_lock(&(this->lock));
    pthread_mutex_destroy(&(this->lock));
    pthread_cond_destroy(&(this->notify));
}

int threadpool::threadpool_destroy(int flags) {
    cout << "Thread pool destroy !" << endl;
    int err = 0;
    if (pthread_mutex_lock(&(this->lock)) != 0) {
        return THREADPOOL_LOCK_FAILURE;
    }
    do {
        /* 如果已经关闭  */
        if (this->shutdown) {
            err = THREADPOOL_SHUTDOWN;
            break;
        }
        // 确定关闭方式，0直接关，1优雅关
        this->shutdown = (flags & THREADPOOL_GRACEFUL) ?
                         graceful_shutdown : immediate_shutdown;

        /* 唤醒所有工作线程 */
        if ((pthread_cond_broadcast(&(this->notify)) != 0) ||
            (pthread_mutex_unlock(&(this->lock)) != 0)) {
            err = THREADPOOL_LOCK_FAILURE;
            break;
        }

        /* 等待所有子线程退出 */
        for (int i = 0; i < this->thread_count; ++i) {
            if (pthread_join(this->threads[i], NULL) != 0) {
                err = THREADPOOL_THREAD_FAILURE;
            }
        }
    } while (false);
    if (err == 0) {
        cout << "thread_pool destroy" << endl;
    }
    return err;
}

void *threadpool::threadpool_thread(void *arg_pool) {
    threadpool *pool = (threadpool *) arg_pool;
    threadpool_task_t task;
    while (1) {
        /* 加锁访问线程池中的成员 */
        pthread_mutex_lock(&(pool->lock));

        /* 阻塞在条件变量上*/
        while ((pool->count == 0) && (!pool->shutdown)) {
            pthread_cond_wait(&(pool->notify), &(pool->lock));
        }

        if ((pool->shutdown == immediate_shutdown) ||
            ((pool->shutdown == graceful_shutdown) &&
             (pool->count == 0))) {
            break;
        }

        /* Grab our task */
        task.function = pool->queue[pool->head].function;
        task.argument = pool->queue[pool->head].argument;
        pool->head = (pool->head + 1) % pool->queue_size;
        pool->count -= 1;

        /* Unlock */
        pthread_mutex_unlock(&(pool->lock));

        /* Get to work */
        (*(task.function))(task.argument);
    }

    --pool->started;

    pthread_mutex_unlock(&(pool->lock));
    pthread_exit(NULL);

    return nullptr;
}


int threadpool_add(threadpool *pool,void (*function)(void *), void *argument, int flags) {
    //printf("add to thread pool !\n");
    int err = 0;

    //(void) flags;
    if (function == nullptr) {
        return THREADPOOL_INVALID;
    }

    if (pthread_mutex_lock(&(pool->lock)) != 0) {
        return THREADPOOL_LOCK_FAILURE;
    }
    int next = (pool->tail + 1) % pool->queue_size;
    do {
        /*是否满*/
        if (pool->count == pool->queue_size) {
            err = THREADPOOL_QUEUE_FULL;
            break;
        }
        /*是否关闭*/
        if (pool->shutdown) {
            err = THREADPOOL_SHUTDOWN;
            break;
        }

        pool->queue[pool->tail].function = function;
        pool->queue[pool->tail].argument = argument;
        pool->tail = next;
        pool->count++;

        /*通知一个线程*/
        if (pthread_cond_signal(&pool->notify) != 0) {
            err = THREADPOOL_LOCK_FAILURE;
            break;
        }
    } while (false);

    if (pthread_mutex_unlock(&pool->lock) != 0) {
        err = THREADPOOL_LOCK_FAILURE;
    }
    return err;
}
