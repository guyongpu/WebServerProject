//
// Created by yongpu on 2/13/20.
//

#ifndef WEBSERVER_10_0_SERVER_H
#define WEBSERVER_10_0_SERVER_H

#include "EventLoop.h"
#include "Channel.h"
#include "EventLoopThreadPool.h"
#include <memory>


class Server
{
public:
    Server(EventLoop *loop, int threadNum, int port);
    ~Server() = default;
    EventLoop* getLoop() const ;
    void start();
    void handNewConn();
    void handThisConn();

private:
    EventLoop *loop_;       // event事件循环
    int threadNum_;         // 线程数目
    std::unique_ptr<EventLoopThreadPool> eventLoopThreadPool_;
    bool started_;          // 服务器开始标志
    std::shared_ptr<Channel> acceptChannel_;
    int port_;              // 端口
    int listenFd_;          // 服务器文件描述符
    static const int MAXFDS = 100000;   // 最大监听数目
};

#endif //WEBSERVER_10_0_SERVER_H
