//
// Created by yongpu on 2/12/20.
//

#include "ThreadPool.h"

// 对静态成员变量初始化
pthread_mutex_t ThreadPool::lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ThreadPool::notify = PTHREAD_COND_INITIALIZER;
std::vector<pthread_t> ThreadPool::threads;
std::vector<ThreadPoolTask> ThreadPool::queue;
int ThreadPool::thread_count = 0;
int ThreadPool::queue_size = 0;
int ThreadPool::head = 0;
int ThreadPool::tail = 0;
int ThreadPool::count = 0;
int ThreadPool::shutdown = 0;
int ThreadPool::started = 0;

int ThreadPool::threadpool_create(int _thread_count, int _queue_size) {
    bool err = false;
    do {
        if (_thread_count <= 0 || _thread_count > MAX_THREADS || _queue_size <= 0 || _queue_size > MAX_QUEUE) {
            _thread_count = 4;
            _queue_size = 1024;
        }

        thread_count = 0;
        queue_size = _queue_size;
        head = tail = count = 0;
        shutdown = started = 0;

        threads.resize(_thread_count);
        queue.resize(_queue_size);

        /* 开始创建工作线程 */
        for (int i = 0; i < _thread_count; ++i) {
            if (pthread_create(&threads[i], NULL, threadpool_thread, (void *) (0)) != 0) {
                //threadpool_destroy(pool, 0);
                return -1;
            }
            ++thread_count;
            ++started;
        }
    } while (false);

    if (err) {
        //threadpool_free(pool);
        return -1;
    }
    return 0;
}

int ThreadPool::threadpool_add(std::shared_ptr<void> args, std::function<void(std::shared_ptr<void>)> fun) {
    int next, err = 0;
    if (pthread_mutex_lock(&lock) != 0) {
        return THREADPOOL_LOCK_FAILURE;
    }
    do {
        next = (tail + 1) % queue_size;
        //队列满
        if (count == queue_size) {
            err = THREADPOOL_QUEUE_FULL;
            break;
        }
        // 已关闭
        if (shutdown) {
            err = THREADPOOL_LOCK_FAILURE;
            break;
        }

        queue[tail].fun = fun;
        queue[tail].args = args;
        ++count;

        // 唤醒一个线程
        if (pthread_cond_signal(&notify) != 0) {
            err = THREADPOOL_LOCK_FAILURE;
            break;
        }
    } while (false);

    if (pthread_mutex_unlock(&lock) != 0) {
        err = THREADPOOL_LOCK_FAILURE;
    }
    return err;
}

// 销毁线程池
int ThreadPool::threadpool_destroy(ShutDownOption shutdown_option) {
    printf("Thread pool destroy !\n");
    int i, err = 0;

    if (pthread_mutex_lock(&lock) != 0) {
        return THREADPOOL_LOCK_FAILURE;
    }
    do {
        if (shutdown > 0) { //如果已经关闭
            err = THREADPOOL_SHUTDOWN;
            break;
        }
        shutdown = shutdown_option; // 关闭方式

        // 获取锁并唤醒所有线程
        if ((pthread_cond_broadcast(&notify) != 0) ||
            (pthread_mutex_unlock(&lock) != 0)) {
            err = THREADPOOL_LOCK_FAILURE;
            break;
        }

        // 结束每个线程
        for (i = 0; i < thread_count; ++i) {
            if (pthread_join(threads[i], NULL) != 0) {
                err = THREADPOOL_THREAD_FAILURE;
            }
        }
    } while (false);

    if (!err) {
        threadpool_free();
    }
    return err;
}

// 释放线程池
int ThreadPool::threadpool_free() {
    if (started > 0) {
        return -1;
    }
    pthread_mutex_lock(&lock);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&notify);
    return 0;
}


// 线程工作函数
void *ThreadPool::threadpool_thread(void *args) {
    while (true) {
        ThreadPoolTask task;
        pthread_mutex_lock(&lock);  // 获取锁
        while ((count == 0) && (!shutdown))  // 任务数为0且线程池未结束
        {
            pthread_cond_wait(&notify, &lock);  // 等待唤醒
        }

        // 如果优雅关闭则等待任务都被执行完后再关闭，直接关闭则立即退出
        if ((shutdown == immediate_shutdown) ||
            ((shutdown == graceful_shutdown) && (count == 0))) {
            break;
        }

        // 获取任务队列队首元素并执行
        task.fun = queue[head].fun;
        task.args = queue[head].args;
        queue[head].fun = NULL;
        queue[head].args.reset();
        head = (head + 1) % queue_size;
        --count;
        pthread_mutex_unlock(&lock);
        (task.fun)(task.args);
    }
    --started;
    pthread_mutex_unlock(&lock);    // 释放锁
    printf("This threadpool thread finishs!\n");
    pthread_exit(NULL);
    return (NULL);
}