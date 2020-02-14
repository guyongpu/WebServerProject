#include <iostream>

#include "EventLoop.h"
#include "Server.h"
#include "base/Logging.h"
#include <getopt.h>
#include <string>
#include <iostream>

using namespace std;


void dealargs(const char *str, const int argc, char *argv[], int &threadNum, string &logPath, int &port);

int main(int argc, char *argv[]) {
    // 初始化参数
    int threadNum = 4;
    int port = 80;
    std::string logPath = "./WebServer.log";
    const char *str = "t:l:p:";
    dealargs(str, static_cast<const int>(argc), argv, threadNum, logPath, port);

    // 设置日志文件路径
    Logger::setLogFileName(logPath);
    // STL库在多线程上应用
#ifndef _PTHREADS
    LOG << "_PTHREADS is not defined !";
#endif
    EventLoop mainLoop;
    Server myHTTPServer(&mainLoop, threadNum, port);
    LOG << "Web Server start now...";
    cout << "myHTTPServer.start()" << endl;
    myHTTPServer.start();
    mainLoop.loop();
    return 0;
}

// 初始化参数
void dealargs(const char *str, const int argc, char *argv[], int &threadNum, string &logPath, int &port) {
    int opt;
    // 形如：sudo ./WebServer -t 4 -l /filename.log -p 8888
    while ((opt = getopt(argc, argv, str)) != -1) {
        switch (opt) {
            case 't': {
                threadNum = atoi(optarg);
                break;
            }
            case 'l': {
                logPath = optarg;
                cout << "logPath = " << logPath << endl;
                if (logPath.size() < 2 || optarg[0] != '/') {
                    printf("logPath should start with \"/\"\n");
                    abort();
                }
                break;
            }
            case 'p': {
                port = atoi(optarg);
                break;
            }
            default:
                break;
        }
    }
}