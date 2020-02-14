//
// Created by yongpu on 2019/12/17.
//

#ifndef WEBSERVER_V2_0_UTIL_H
#define WEBSERVER_V2_0_UTIL_H


#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

using namespace std;

ssize_t readn(int fd, void *buff, size_t n);

ssize_t writen(int fd, void *buff, size_t n);

void handle_for_sigpipe();

int setSocketNonBlocking(int fd);

#endif //WEBSERVER_V2_0_UTIL_H
