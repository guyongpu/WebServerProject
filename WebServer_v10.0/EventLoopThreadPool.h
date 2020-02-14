//
// Created by yongpu on 2/13/20.
//

#ifndef WEBSERVER_10_0_EVENTLOOPTHREADPOOL_H
#define WEBSERVER_10_0_EVENTLOOPTHREADPOOL_H


#include "base/noncopyable.h"
#include "EventLoopThread.h"
#include "base/Logging.h"
#include <memory>
#include <vector>

class EventLoopThreadPool : noncopyable
{
public:
    EventLoopThreadPool(EventLoop* baseLoop, int numThreads);

    ~EventLoopThreadPool()
    {
        LOG << "~EventLoopThreadPool()";
    }
    void start();

    EventLoop *getNextLoop();

private:
    EventLoop* baseLoop_;
    bool started_;
    int numThreads_;
    int next_;
    std::vector<std::shared_ptr<EventLoopThread>> threads_;
    std::vector<EventLoop*> loops_;
};

#endif //WEBSERVER_10_0_EVENTLOOPTHREADPOOL_H
