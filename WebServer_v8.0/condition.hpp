//
// Created by yongpu on 2020/1/12.
//

#ifndef WEBSERVER_V8_0_CONDITION_HPP
#define WEBSERVER_V8_0_CONDITION_HPP

#include "nocopyable.hpp"
#include "mutexLock.hpp"
#include <pthread.h>


class Condition : noncopyable {
public:
    explicit Condition(MutexLock &_mutex) :
            mutex(_mutex) {
        pthread_cond_init(&cond,NULL);
    }

    ~Condition() {
        pthread_cond_destroy(&cond);
    }

    void wait() {
        pthread_cond_wait(&cond, mutex.get());
    }

    void notify() {
        pthread_cond_signal(&cond);
    }

    void notifyAll() {
        pthread_cond_broadcast(&cond);
    }

private:
    MutexLock &mutex;
    pthread_cond_t cond;
};

#endif //WEBSERVER_V8_0_CONDITION_HPP