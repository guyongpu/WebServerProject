//
// Created by yongpu on 2/12/20.
//

#include "Timer.h"

/********************* TimerNode *********************/
TimerNode::TimerNode(std::shared_ptr<HttpData> requestData, int timeout) {
    deleted_ = false;
    SPHttpData = requestData;

    // 设置超时时间
    struct timeval now;
    gettimeofday(&now, NULL);
    // 以毫秒计
    expiredTime_ = (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000)) + timeout;
}

TimerNode::~TimerNode() {
    if(SPHttpData){
        SPHttpData->handleClose();
    }
}

TimerNode::TimerNode(TimerNode &tn) {
    SPHttpData=tn.SPHttpData;
}

// 重新设置超时时间
void TimerNode::update(int timeout) {
    struct timeval now;
    gettimeofday(&now, NULL);
    expiredTime_ = (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000)) + timeout;
}

// 判断是否超时
bool TimerNode::isValid() {
    struct timeval now;
    gettimeofday(&now, NULL);
    size_t temp = (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000));
    if (temp < expiredTime_)
        return true;
    else
    {
        this->setDeleted(); // 设置删除
        return false;
    }
}

// 清除请求数据requestData
void TimerNode::clearReq() {
    SPHttpData.reset(); // 引用计数减1
    this->setDeleted(); // 设置删除
}

void TimerNode::setDeleted() {
    this->deleted_ = true;
}

bool TimerNode::isDeleted() const {
    return this->deleted_;
}

size_t TimerNode::getExpTime() const {
    return this->expiredTime_;
}

/********************* TimerManager *********************/

TimerManager::TimerManager() {

}

TimerManager::~TimerManager() {

}

// 增加一个定时器
void TimerManager::addTimer(std::shared_ptr<HttpData> SPHttpData, int timeout)
{
    SPTimerNode new_node(new TimerNode(SPHttpData, timeout));   // 新建一个并初始化智能指针
    timerNodeQueue.push(new_node);      // 加到timerNode队列
    SPHttpData->linkTimer(new_node);    // 将定时器关联到请求
}


/* 处理逻辑是这样的~
因为(1) 优先队列不支持随机访问
(2) 即使支持，随机删除某节点后破坏了堆的结构，需要重新更新堆结构。
所以对于被置为deleted的时间节点，会延迟到它(1)超时 或 (2)它前面的节点都被删除时，它才会被删除。
一个点被置为deleted,它最迟会在TIMER_TIME_OUT时间后被删除。
这样做有两个好处：
(1) 第一个好处是不需要遍历优先队列，省时。
(2) 第二个好处是给超时时间一个容忍的时间，就是设定的超时时间是删除的下限(并不是一到超时时间就立即删除)，如果监听的请求在超时后的下一次请求中又一次出现了，
就不用再重新申请RequestData节点了，这样可以继续重复利用前面的RequestData，减少了一次delete和一次new的时间。
*/

// 处理超时的定时器
void TimerManager::handleExpiredEvent()
{
    //MutexLockGuard locker(lock);
    while (!timerNodeQueue.empty())
    {
        SPTimerNode ptimer_now = timerNodeQueue.top();
        if (ptimer_now->isDeleted())
            timerNodeQueue.pop();
        else if (ptimer_now->isValid() == false)
            timerNodeQueue.pop();
        else
            break;
    }
}