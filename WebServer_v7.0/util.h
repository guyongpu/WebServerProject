//
// Created by yongpu on 2020/1/11.
//

#ifndef WEBSERVER_V7_0_UTIL_H
#define WEBSERVER_V7_0_UTIL_H

#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <cstdlib>

ssize_t readn(int fd, void *buff, size_t n);

ssize_t writen(int fd, void *buff, size_t n);

void handle_for_sigpipe();

int setSocketNonBlocking(int fd);

#endif //WEBSERVER_V7_0_UTIL_H
