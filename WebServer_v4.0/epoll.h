//
// Created by yongpu on 2020/1/7.
//

#ifndef WEBSERVER_V2_0_EPOLL_H
#define WEBSERVER_V2_0_EPOLL_H

#include "requestData.h"
#include <iostream>

using namespace std;

const int MAXEVENTS = 5000;
const int LISTENQ = 1024;


int epoll_init();
int epoll_add(int epoll_fd, int fd, void *request, __uint32_t events);
int epoll_mod(int epoll_fd, int fd, void *request, __uint32_t events);
int epoll_del(int epoll_fd, int fd, void *request, __uint32_t events);
int my_epoll_wait(int epoll_fd, struct epoll_event *events, int max_events, int timeout);

int epoll_init();


#endif //WEBSERVER_V2_0_EPOLL_H
