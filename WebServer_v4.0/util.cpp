//
// Created by yongpu on 2019/12/17.
//

#include "util.h"

/* 读函数read
 * ssize_t read(int fd,void *buf,size_t nbyte)
 * read函数是负责从fd中读取内容。
 * 当读成功时，read返回实际所读的字节数。
 * 如果返回的值是0，表示已经读到文件的结束了。
 * 小于0表示出现了错误。如果错误为EINTR说明读是由中断引起的，如果是ECONNREST表示网络连接出了问题。
 */
ssize_t readn(int fd, void *buff, size_t n) {
    size_t nleft = n;
    ssize_t nread = 0;
    ssize_t readSum = 0;
    char *ptr = (char *) buff;
    while (nleft > 0) {
        nread = read(fd, ptr, nleft);
        if (nread < 0) {  /* 出错 */
            if (errno == EINTR) {   /* 中断引起的，可以继续读 */
                nread = 0;
            } else if (errno == EAGAIN) {
                return readSum;
            } else {
                return -1;
            }
        } else if (nread == 0) {
            break;
        } else {
            readSum = readSum + nread;
            nleft = nleft - nread;
            ptr = ptr + nread;
        }
    }
    return readSum;
}

/* 写函数write
 * ssize_t write(int fd,const void *buf,size_t nbytes)
 * write函数将buf中的nbytes字节内容写入文件描述符fd。成功时返回写的字节数，失败时返回-1，并设置errno变量。
 * 在网络程序中,当我们向套接字文件描述符写时有俩种可能：
 * 1) write的返回值大于0，表示写了部分或者是全部的数据；
 * 2) 返回的值小于0，此时出现了错误，我们要根据错误类型来处理。
 * 如果错误为EINTR表示在写的时候出现了中断错误。如果为EPIPE表示网络连接出现了问题（对方已经关闭了连接）。
 */
ssize_t writen(int fd, void *buff, size_t n) {
    size_t nleft = n;
    ssize_t nwriteen = 0;
    ssize_t writeSum = 0;
    char *ptr = (char *) buff;
    while (nleft > 0) {
        nwriteen = write(fd, ptr, nleft);
        if (nwriteen <= 0) {
            if (nwriteen < 0) {
                if (errno == EINTR || errno == EAGAIN) {
                    nwriteen = 0;
                    continue;
                } else {
                    return -1;
                }
            }
        } else {
            writeSum = writeSum + nwriteen;
            nleft = nleft - nwriteen;
            ptr = ptr + nwriteen;
        }
    }
    return writeSum;
}

/* 设置SIGPIPE异常的处理为SIG_IGN，即忽略 */
void handle_for_sigpipe() {
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = SIG_IGN;    /* 信号处理方式/函数,SIG_IGN为设定接受到指定信号后的动作为忽略 */
    sa.sa_flags = 0;
    /* SIGPIPE信号, 该信号默认结束进程 */
    if (sigaction(SIGPIPE, &sa, NULL)) {    /* 注册SIGPIPE信号 */
        return;
    }
}

/* 设置文件描述符为非阻塞 */
int setSocketNonBlocking(int fd) {
    int flag = fcntl(fd, F_GETFL, 0);   /* 获取文件描述符属性 */
    if (flag == -1) {
        perror("fcntl F_GETFL error");
        return -1;
    }
    flag = flag | O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flag) == -1) {
        perror("fcntl F_SETFL error");
        return -1;
    }
    return 0;
}
