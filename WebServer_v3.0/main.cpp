//
// Created by yongpu on 2019/12/18.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cassert>
#include <sys/epoll.h>
#include <exception>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>


#include "locker.h"
#include "threadpool.h"
#include "http_conn.h"


#define MAX_FD 65536
#define MAX_EVENT_NUMBER 10000

extern int addFd(int epollfd, int fd, bool one_shot);

extern int removeFd(int epollfd, int fd);

void addSig(int sig, void(handler)(int), bool restart = true);

void show_error(int connfd, const char *info);

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        printf("usage:%s ip_address port_number\n", basename(argv[0]));
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    addSig(SIGPIPE, SIG_IGN);

    threadpool< http_conn >* pool = NULL;


    return 0;
}

/* 添加信号 */
void addSig(int sig, void(handler)(int), bool restart) {
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = handler;
    if (restart) {
        sa.sa_flags = sa.sa_flags | SA_RESTART;
    }
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, NULL) != -1);
}

/* 显示错误 */
void show_error(int connfd, const char *info) {
    printf("%s", info);
    send(connfd, info, strlen(info), 0);
    close(connfd);
}