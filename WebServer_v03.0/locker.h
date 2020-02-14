//
// Created by yongpu on 2019/12/18.
//

#ifndef WEBSERVER_V4_0_LOCKER_H
#define WEBSERVER_V4_0_LOCKER_H

#include <exception>
#include <pthread.h>
#include <semaphore.h>

/******************************************************/
/* 信号量,用作计数 */
class sem {
public:
    sem() {
        if (sem_init(&m_sem, 0, 0) != 0) {
            throw std::exception();
        }
    }

    ~sem() {
        sem_destroy(&m_sem);
    }

    bool wait() {
        return sem_wait(&m_sem);    // 信号量-1
    }

    bool post() {
        return sem_post(&m_sem);    // 信号量+1
    }

private:
    sem_t m_sem;

};

/******************************************************/
/* 互斥锁，用于保护任务队列 */
class locker {
public:
    locker() {
        if (pthread_mutex_init(&m_mutex, NULL) != 0) {
            throw std::exception();
        }
    }

    ~locker() {
        pthread_mutex_destroy(&m_mutex);
    }

    bool lock() {
        return pthread_mutex_lock(&m_mutex);
    }

    bool unlock() {
        return pthread_mutex_unlock(&m_mutex);
    }

private:
    pthread_mutex_t m_mutex;
};

/******************************************************/
/* 条件变量，用于线程同步 */
class cond {
public:
    cond() {
        if (pthread_mutex_init(&m_mutex, NULL) != 0) {
            throw std::exception();
        }
        if (pthread_cond_init(&m_cond, NULL) != 0) {
            pthread_mutex_destroy(&m_mutex);
            throw std::exception();
        }
    }

    ~cond() {
        pthread_mutex_destroy(&m_mutex);
        pthread_cond_destroy(&m_cond);
    }

    /** 在条件变量m_cond上等待被唤醒 */
    bool wait() {
        int ret = 0;
        pthread_mutex_lock(&m_mutex);
        ret = pthread_cond_wait(&m_cond, &m_mutex);
        pthread_mutex_unlock(&m_mutex);
        return ret == 0;
    }

    /** 唤醒一个在条件变量m_cond上等待的线程 */
    bool signal() {
        return pthread_cond_signal(&m_cond);
    }

private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
};

#endif //WEBSERVER_V4_0_LOCKER_H
