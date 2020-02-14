//
// Created by yongpu on 2/12/20.
//

#ifndef WEBSERVER_10_0_TIMER_H
#define WEBSERVER_10_0_TIMER_H

#include "HttpData.h"
#include "base/noncopyable.h"
#include "base/MutexLock.h"
#include <unistd.h>
#include <sys/time.h>
#include <memory>
#include <queue>
#include <deque>


class HttpData;

class TimerNode {
public:
    TimerNode(std::shared_ptr<HttpData> requestData, int timeout);

    ~TimerNode();

    TimerNode(TimerNode &tn);

    void update(int timeout);

    bool isValid();

    void clearReq();

    void setDeleted();

    bool isDeleted() const;

    size_t getExpTime() const;

private:
    bool deleted_;
    size_t expiredTime_;
    std::shared_ptr<HttpData> SPHttpData;
};

struct TimerCmp {
    bool operator()(std::shared_ptr<TimerNode> &a, std::shared_ptr<TimerNode> &b) const {
        return a->getExpTime() > b->getExpTime();
    }
};

// 管理定时器的类
class TimerManager {
public:
    TimerManager();

    ~TimerManager();

    void addTimer(std::shared_ptr<HttpData> SPHttpData, int timeout);

    void handleExpiredEvent();

private:
    typedef std::shared_ptr<TimerNode> SPTimerNode;
    std::priority_queue<SPTimerNode, std::deque<SPTimerNode>, TimerCmp> timerNodeQueue;
    //MutexLock lock;
};

#endif //WEBSERVER_10_0_TIMER_H
