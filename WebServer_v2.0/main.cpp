#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096    /* 缓冲区大小 */

/* 主状态机的两种可能状态，分别表示：当前正在分析请求行，当前正在分析头部字段 */
enum CHECK_STATE {
    CHECK_STATE_REQUESTLINE = 0, CHECK_STATE_HEADER
};

/* 从状态机的三种可能，即行的读取状态，分别表示：读取到一个完整的行、行出错和行数据尚且不完整 */
enum LINE_STATUS {
    LINE_OK = 0, LINE_BAD, LINE_OPEN
};

/* 服务器处理HTTP请求的结果：
 * NO_REQUEST 表示请求不完整，需要继续读取客户端数据；
 * GET_REQUST 表示获得了一个完整的客户端请求;
 * BAD_REQUST 表示客户端请求语法有问题；
 * FORBIDDEN_REQUEST 表示客户对资源没有足够的访问权限;
 * INTERNAL_ERROR 表示服务器内部错误；
 * CLOSE_CONNECTION 表示客户端已经关闭连接了;
 */
enum HTTP_CODE {
    NO_REQUEST, GET_REQUST, BAD_REQUST, FORBIDDEN_REQUEST, INTERNAL_ERROR, CLOSE_CONNECTION
};

/* 应答内容，为了简化信息，不给客户端一个完整的HHTP应答报文，而是根据服务器的处理结果发送如下成功或失败信息 */
static const char *szret[] = {"I get a correct result\n", "Something wrong\n"};

/* 从状态机，用于解析出一行的内容 */
LINE_STATUS parse_line(char *buff, int &checked_index, int &read_index);

/* 分析请求行 */
HTTP_CODE parse_requestline(char *temp, CHECK_STATE &checkState);

/* 分析头部字段 */
HTTP_CODE parse_headers(char *temp);

/* 分析HTTP请求的入口函数 */
HTTP_CODE parse_content(char *buffer, int &checked_index, CHECK_STATE &checkState, int &read_index, int &start_line);


int main(int argc, char *argv[]) {
    const char *ip = "127.0.0.1";
    int port = 8888;
    if (argc <= 2) {
        printf("usage:%s ip_address port_number\n", basename(argv[0]));
    } else {
        ip = argv[1];
        port = atoi(argv[2]);
    }

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);
    int ret = bind(listenfd, (struct sockaddr *) &address, sizeof(address));
    assert(ret != -1);

    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    ret = listen(listenfd, 5);
    assert(ret != -1);

    struct sockaddr_in client_address;
    socklen_t client_addr_length = sizeof(client_address);

    printf("server runing...\n");
    while (1) {
        int fd = accept(listenfd, (struct sockaddr *) &client_address, &client_addr_length);

        if (fd < 0) {
            printf("errno is %d", errno);
        } else {
            char buffer[BUFFER_SIZE];   /* 读缓冲区 */
            memset(buffer, '\0', BUFFER_SIZE);
            int data_read = 0;
            int read_index = 0;     /* 当前已经读取了多少字节的客户数据 */
            int checked_index = 0;  /* 当前已经分析完了多少字节的客户数据 */
            int start_line = 0;     /* 行在buffer中的起始位置 */

            /* 设置主状态机的初始状态 */
            CHECK_STATE checkState = CHECK_STATE_REQUESTLINE;
            while (1) {
                data_read = recv(fd, buffer + read_index, BUFFER_SIZE - read_index, 0);
                /*
                 * 使用curl 127.0.0.1:8888/index.html 的请求报文如下：
                 * ----------------------------------------
                 *  GET /index.html HTTP/1.1
                 *  Host: 127.0.0.1:9999
                 *  User-Agent: curl/7.58.0
                 *  Accept: *//*
                 *
                 *
                 * ----------------------------------------
                 *
                 * 程序输出为：
                 * ----------------------------------------
                 * The request method is GET
                 * The request URL is :/index.html
                 * the request host is: 127.0.0.1:9999
                 * ----------------------------------------
                 */
                printf("----------------------------------------\n");
                printf("%s\n", buffer);
                printf("----------------------------------------\n");
                if (data_read == -1) {
                    printf("reading failed\n");
                    break;
                } else if (data_read == 0) {
                    printf("remote client has closed the connection\n");
                    break;
                }
                read_index = read_index + data_read;
                /* 分析目前已获得的所有客户数据 */
                HTTP_CODE result = parse_content(buffer, checked_index, checkState, read_index, start_line);

                if (result == NO_REQUEST) {             /* 尚未得到一个完整的HTTP请求 */
                    continue;
                } else if (result == GET_REQUST) {      /* 得到一个完整的、正确的HTTP请求 */
                    printf("response:%s\n", szret[0]);
                    send(fd, szret[0], strlen(szret[0]), 0);
                    break;
                } else {                                  /* 其他情况均发生错误 */
                    printf("response:%s\n", szret[1]);
                    send(fd, szret[1], strlen(szret[1]), 0);
                    break;
                }
            }
            close(fd);
        }
    }
    printf("server stop...\n");
    close(listenfd);
    return 0;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

/* 从状态机，用于解析出一行的内容 */
LINE_STATUS parse_line(char *buffer, int &checked_index, int &read_index) {
    char temp;
    /* checked_index 指向buffer（应用程序的读缓冲区）中当前正在分析的字节，read_index指向buffer中客户数据的尾部的下一字节.
     * buffer中第0~checked_index字节都已经分析完毕，第checked_index~（read_index-1)字节由下面的循环挨个分析
     */
    for (; checked_index < read_index; checked_index++) {
        /* 获得当前要分析的字节 */
        temp = buffer[checked_index];
        /* 如果当前字节是"\r",即回车符，则说明可能读到一个完整的行 */
        if (temp == '\r') {
            /* 如果当前是本行最后一个字符，则说明不完整，需要更多数据
             * 如果下一个字符是'\n'则说明读取到了完整的行
             * 否则说明HTTP请求存在语法问题
             */
            if (checked_index + 1 == read_index) {
                return LINE_OPEN;
            }
                /* 如果下一个字符是'\n'，则说明我们成功读取到一个完整的行 */
            else if (buffer[checked_index + 1] == '\n') {
                /* 将 '\r\n' 替换为 '\0\0' */
                buffer[checked_index] = '\0';
                checked_index++;
                buffer[checked_index] = '\0';
                checked_index++;
                return LINE_OK;
            }
            /* 否则的话，说明客户发送的HTTP请求语法有问题 */
            return LINE_BAD;
        }
            /* 如果当前的字符是'\n'，即换行符，则也说明可能读取到一个完整的行 */
        else if (temp == '\n') {
            if ((checked_index > 1) && buffer[checked_index - 1] == '\n') {
                buffer[checked_index] = '\0';
                checked_index++;
                buffer[checked_index] = '\0';
                checked_index++;
                return LINE_OK;
            } else {
                return LINE_BAD;
            }
        }
    }
    /* 如果所有内容都分析完毕也没有遇到'\r'字符，则返回LINE_OPEN，表示还需要继续读取客户数据才能进一步分析 */
    return LINE_OPEN;
}

/* 分析请求行 */
HTTP_CODE parse_requestline(char *temp, CHECK_STATE &checkState) {
    /* strpbrk:依次检验字符串s1中的字符，当被检验字符在字符串s2中也包含时，则停止检验，并返回该字符位置，空字符null不包括在内。 */
    char *url = strpbrk(temp, " \t");
    if (!url) {
        return BAD_REQUST;
    }
    *url++ = '\0';
    char *method = temp;
    if (strcasecmp(method, "GET") == 0) /* 仅支持GET方法 */
    {
        printf("The request method is GET\n");
    } else {
        return BAD_REQUST;
    }

    /* strspn函数统计缓冲区前面多少个连续字符在字符集合中 */
    url = url + strspn(url, " \t");   /* 排除 '\t'和空格 */
    char *version = strpbrk(url, " \t");
    if (!version) {
        return BAD_REQUST;
    }
    *version++ = '\0';
    version += strspn(version, " \t");
    /* 仅支持HTTP/1.1 */
    if (strcasecmp(version, "HTTP/1.1") != 0) {
        return BAD_REQUST;
    }
    /* 检查URL是否合法 */
    if (strncasecmp(url, "http://", 7) == 0) {   /* 匹配前7个字符 */
        url = url + 7;
        url = strchr(url, '/');  /* 首次出现'/'的位置 */
    }
    printf("The request URL is :%s \n", url);
    /* HTTP 请求行处理完毕，状态转移到头部字段的分析 */
    checkState = CHECK_STATE_HEADER;
    return NO_REQUEST;      /* 表示请求不完整，需要继续读取客户端数据； */
}

/* 分析头部字段 */
HTTP_CODE parse_headers(char *temp) {
    /* 遇到一个空行，说明我们得到了一个正确的HTTP请求 */
    if (temp[0] == '\0') {
        return GET_REQUST;
    } else if (strncasecmp(temp, "Host:", 5) == 0) /* 处理“HOST”头部字段 */
    {
        temp = temp + 5;
        temp = temp + strspn(temp, " \t");
        printf("the request host is: %s\n", temp);
    } else {  /* 其他头部字段都不处理 */
        printf("I can not handle this header\n");
    }
    return NO_REQUEST;
}

/* 分析HTTP请求的入口函数 */
HTTP_CODE
parse_content(char *buffer, int &checked_index, CHECK_STATE &checkState, int &read_index, int &start_line) {
    LINE_STATUS lineStatus = LINE_OK;   /* 记录当前行的读取状态 */
    HTTP_CODE retCode = NO_REQUEST;     /* 记录HTTP请求的处理结果 */
    /*主状态机，用于从buffer中取出所有完整的行 */
    while ((lineStatus = parse_line(buffer, checked_index, read_index)) == LINE_OK) {
        char *temp = buffer + start_line;
        start_line = checked_index;
        switch (checkState) {
            case CHECK_STATE_REQUESTLINE:   /* 第一个状态 */
            {
                retCode = parse_requestline(temp, checkState);
                if (retCode == BAD_REQUST) {
                    return BAD_REQUST;
                }
                break;
            }
            case CHECK_STATE_HEADER:        /* 第二个状态 */
            {
                retCode = parse_headers(temp);
                if (retCode == BAD_REQUST) {
                    return BAD_REQUST;
                } else if (retCode == GET_REQUST) {
                    return GET_REQUST;
                }
                break;
            }
            default: {
                return INTERNAL_ERROR;
            }
        }//switch
    }// while
    if (lineStatus == LINE_OPEN) {    /* 若没有读取到一个完整的行，则表示还需要继续读取客户数据才能进一步分析 */
        return NO_REQUEST;
    } else {
        return BAD_REQUST;
    }
}
