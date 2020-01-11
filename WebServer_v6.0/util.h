//
// Created by yongpu on 2020/1/10.
//

#ifndef WEBSERVER_V6_0_UTIL_H
#define WEBSERVER_V6_0_UTIL_H

#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

ssize_t readn(int fd, void *buff, size_t n);

ssize_t writen(int fd, void *buff, size_t n);

void handle_for_sigpipe();

int setSocketNonBlocking(int fd);


#endif //WEBSERVER_V6_0_UTIL_H
