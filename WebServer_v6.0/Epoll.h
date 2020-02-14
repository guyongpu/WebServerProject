//
// Created by yongpu on 2020/1/10.
//

#ifndef WEBSERVER_V6_0_EPOLL_H
#define WEBSERVER_V6_0_EPOLL_H

#include "requestData.h"
#include "threadpool.h"
#include "util.h"

#include <vector>
#include <unordered_map>
#include <sys/epoll.h>
#include <memory>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <queue>
#include <deque>
#include <arpa/inet.h>
#include <iostream>

using namespace std;


class Epoll {
private:

    static epoll_event *events;
    static unordered_map<int, shared_ptr<requestData>> fd2req;
    static int epoll_fd;    /*红黑树的树根*/
    static const string PATH;
public:
    static int epoll_init(int maxevents, int listen_num);

    static int epoll_add(int fd, std::shared_ptr<requestData> request, __uint32_t events);

    static int epoll_mod(int fd, std::shared_ptr<requestData> request, __uint32_t events);

    static int epoll_del(int fd, __uint32_t events);

    static void my_epoll_wait(int listen_fd, int max_events, int timeout);

    static void acceptConnection(int listen_fd, int epoll_fd, const std::string path);

    static std::vector<std::shared_ptr<requestData>>
    getEventsRequest(int listen_fd, int events_num, const std::string path);
};


#endif //WEBSERVER_V6_0_EPOLL_H
