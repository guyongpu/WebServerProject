//
// Created by yongpu on 2020/1/8.
//

#ifndef WEBSERVER_V5_0_UTIL_H
#define WEBSERVER_V5_0_UTIL_H

#include <cstdlib>

ssize_t readn(int fd, void *buff, size_t n);

ssize_t writen(int fd, void *buff, size_t n);

void handle_for_sigpipe();

int setSocketNonBlocking(int fd);

#endif //WEBSERVER_V5_0_UTIL_H
