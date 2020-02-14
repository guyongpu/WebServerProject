//
// Created by yongpu on 2020/1/12.
//

#ifndef WEBSERVER_V8_0_MUTEXLOCK_HPP
#define WEBSERVER_V8_0_MUTEXLOCK_HPP

#include "nocopyable.hpp"
#include <pthread.h>
#include <cstdio>

/* 任务队列锁 */
class MutexLock : noncopyable {
public:
    MutexLock() {
        pthread_mutex_init(&mutex, NULL);
    }

    ~MutexLock() {
        pthread_mutex_lock(&mutex);
        pthread_mutex_destroy(&mutex);
    }

    void lock() {
        pthread_mutex_lock(&mutex);
    }

    void unlock() {
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_t *get() {
        return &mutex;
    }
    // 友元类不受访问权限影响

private:
    pthread_mutex_t mutex;
private:
    friend class Condition;
};

/*时间堆Rall锁*/
class MutexLockGuard : noncopyable {
public:
    explicit MutexLockGuard(MutexLock &_mutex) :
            mutex(_mutex) {
        mutex.lock();
    }

    ~MutexLockGuard() {
        mutex.unlock();
    }

private:
    MutexLock &mutex;
};

#endif //WEBSERVER_V8_0_MUTEXLOCK_HPP
