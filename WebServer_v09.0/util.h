//
// Created by yongpu on 2/4/20.
//

#ifndef WEBSERVER_V9_0_UTIL_H
#define WEBSERVER_V9_0_UTIL_H


#include <cstdlib>
#include <string>

ssize_t readn(int fd, void *buff, size_t n);
ssize_t readn(int fd, std::string &inBuffer);
ssize_t writen(int fd, void *buff, size_t n);
ssize_t writen(int fd, std::string &sbuff);
void handle_for_sigpipe();
int setSocketNonBlocking(int fd);

#endif //WEBSERVER_V9_0_UTIL_H
