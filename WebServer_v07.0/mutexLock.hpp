//
// Created by yongpu on 2020/1/11.
//

#ifndef WEBSERVER_V7_0_MUTEXLOCK_HPP
#define WEBSERVER_V7_0_MUTEXLOCK_HPP

#include <pthread.h>
#include <cstdio>
#include "nocopyable.hpp"

/*任务队列锁*/
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

private:
    pthread_mutex_t mutex;
};

/*RALL锁*/
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

#endif //WEBSERVER_V7_0_MUTEXLOCK_HPP
