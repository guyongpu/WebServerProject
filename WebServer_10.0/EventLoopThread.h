//
// Created by yongpu on 2/13/20.
//

#ifndef WEBSERVER_10_0_EVENTLOOPTHREAD_H
#define WEBSERVER_10_0_EVENTLOOPTHREAD_H


#include "base/Condition.h"
#include "base/MutexLock.h"
#include "base/Thread.h"
#include "base/noncopyable.h"
#include "EventLoop.h"

class EventLoopThread :noncopyable
{
public:
    EventLoopThread();
    ~EventLoopThread();
    EventLoop* startLoop();

private:
    void threadFunc();
    EventLoop *loop_;
    bool exiting_;
    Thread thread_;
    MutexLock mutex_;
    Condition cond_;
};


#endif //WEBSERVER_10_0_EVENTLOOPTHREAD_H
