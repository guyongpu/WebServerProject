//
// Created by yongpu on 2019/12/18.
//

#ifndef WEBSERVER_V4_0_THREADPOOL_H
#define WEBSERVER_V4_0_THREADPOOL_H

#include <iostream>
#include <list>
#include <cstdio>
#include <exception>
#include <pthread.h>
#include "locker.h"

using namespace std;

template<typename T>
class threadpool {
public:
    threadpool(int thread_number = 8, int max_requests = 1000) {
        m_thread_number = thread_number;
        m_max_requests = max_requests;
        m_stop = false;
        m_threads = nullptr;

        // 参数设置错误则抛出错误
        if (thread_number <= 0 || m_max_requests <= 0) {
            throw exception();
        }

        m_threads = new pthread_t[m_thread_number]; // new number个线程指针
        if (!m_threads) { // new 失败
            throw exception();
        }

        for (int i = 0; i < thread_number; i++) {
            cout << "create the %dth thread" << endl;

            if (pthread_create(m_threads[i], NULL, worker, this) != 0) {    // 线程创建失败
                delete[]m_threads;
                throw exception();
            }
            if (pthread_detach(m_threads[i]) != 0) { // 线程分离错误
                delete[] m_threads;
                throw exception();
            }
        }


    }

    // 销毁线程池
    ~threadpool() {
        delete[]m_threads;
        m_stop = true;
    }

    // 向任务队列中添加task
    bool append(T *request) {
        m_queuelocker.lock();   // 加锁,访问任务队列m_workqueue
        if (m_workqueue.size() > m_max_requests) {
            m_queuelocker.unlock(); // 解锁
            return false;
        }
        m_workqueue.push_back(request);
        m_queuelocker.unlock();
        m_queuestat.post(); // 原子操作，信号量+1,表示任务当前的数量
        return true;
    }

private:
    static void *worker(void *arg) {
        threadpool *pool = (threadpool *) arg;
        pool->run();
        return pool;
    }

    // 管理者线程运行函数
    void run() {
        while (!m_stop) {
            m_queuestat.wait();
            m_queuelocker.lock();
            if (m_workqueue.empty()) {          // 任务队列为空
                m_queuelocker.unlock();
                continue;
            }
            T *request = m_workqueue.front();   // 取出队首第一个任务
            m_workqueue.pop_back();             // 删除队首任务
            m_queuelocker.unlock();

            if (request == nullptr) {           // 任务指针为nullptr
                continue;
            }

            request->process();                 // 业务处理函数
        }
    }

private:
    int m_thread_number;
    int m_max_requests;
    pthread_t *m_threads;
    list<T *> m_workqueue;
    locker m_queuelocker;
    sem m_queuestat;
    bool m_stop;
};


#endif //WEBSERVER_V4_0_THREADPOOL_H
