//
// Created by yongpu on 2/4/20.
//

#ifndef WEBSERVER_V9_0_COUNTDOWNLATCH_H
#define WEBSERVER_V9_0_COUNTDOWNLATCH_H

#include "Condition.h"
#include "MutexLock.h"

#include "noncopyable.h"

class CountDownLatch : noncopyable
{
public:
    explicit CountDownLatch(int count);
    void wait();
    void countDown();
    int getCount() const;

private:
    mutable MutexLock mutex_;
    Condition condition_;
    int count_;
};

#endif //WEBSERVER_V9_0_COUNTDOWNLATCH_H
