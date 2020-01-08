//
// Created by yongpu on 2020/1/7.
//

#ifndef WEBSERVER_V2_0_REQUESTDATA_H
#define WEBSERVER_V2_0_REQUESTDATA_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <queue>

using namespace std;

// HTTP状态机解析
const int STATE_PARSE_URI = 1;
const int STATE_PARSE_HEADERS = 2;
const int STATE_RECV_BODY = 3;
const int STATE_ANALYSIS = 4;
const int STATE_FINISH = 5;

const int MAX_BUFF = 4096;

// 有请求出现但是读不到数据,可能是Request Aborted,
// 或者来自网络的数据没有达到等原因,
// 对这样的请求尝试超过一定的次数就抛弃
const int AGAIN_MAX_TIMES = 200;

// 所有可能的解析结果
// URI
const int PARSE_URI_AGAIN = -1;
const int PARSE_URI_ERROR = -2;
const int PARSE_URI_SUCCESS = 0;

// HEADER
const int PARSE_HEADER_AGAIN = -1;
const int PARSE_HEADER_ERROR = -2;
const int PARSE_HEADER_SUCCESS = 0;

const int ANALYSIS_ERROR = -2;
const int ANALYSIS_SUCCESS = 0;

// HTTP 请求方法
const int METHOD_POST = 1;
const int METHOD_GET = 2;
const int HTTP_10 = 1;
const int HTTP_11 = 2;

const int EPOLL_WAIT_TIME = 500;

const int TIME_OUT = 5000;  // 请求超时时间为5000ms，即5s

// 向前声明
struct mytimer;
struct requestData;

/*********************************************************************/
/**                            MimeType                             **/
/*********************************************************************/

class MimeType {
private:
    static pthread_mutex_t lock;
    static std::unordered_map<std::string, std::string> mime;

    MimeType();

    MimeType(const MimeType &m);

public:
    static string getMime(const std::string &suffix);
};



/*********************************************************************/
/**                            requestData                          **/
/*********************************************************************/
// 请求头的解析
enum HeadersState {
    h_start = 0,
    h_key,
    h_colon,
    h_spaces_after_colon,
    h_value,
    h_CR,
    h_LF,
    h_end_CR,
    h_end_LF
};

// 请求头解析出来的信息存放的数据结构
struct requestData {
private:
    int againTimes; // 重复次数
    string path;
    int fd;
    int epollfd;
    // content的内容用完就清
    string content;
    int method;
    int HTTPversion;
    string file_name;
    int now_read_pos;
    int state;
    int h_state;
    bool isfinish;
    bool keep_alive;
    std::unordered_map<std::string, std::string> headers;
    mytimer *timer;


private:
    bool process_state_machine(bool &isError);

    int parse_URI();    // 解析URI

    int parse_Headers();    // 解析头

    int analysisRequest();  // 解析请求

public:

    requestData();

    requestData(int _epollfd, int _fd, std::string _path);

    ~requestData();

    void addTimer(mytimer *mtimer);

    void reset();

    void seperateTimer();

    int getFd();

    void setFd(int _fd);

    void handleRequest();

    void handleError(int fd, int err_num, std::string short_msg);
};

/*********************************************************************/
/**                            mytimer                              **/
/*********************************************************************/

struct mytimer {
    bool deleted;
    size_t expired_time;
    requestData *request_data;

    mytimer(requestData *_request_data, int timeout);

    ~mytimer();

    void update(int timeout);

    bool isvalid();

    void clearReq();

    void setDeleted();

    bool isDeleted() const;

    size_t getExpTime() const;
};

struct timerCmp {
    bool operator()(const mytimer *a, const mytimer *b) const;
};

/*********************************************************************/
/**                            TimerQueue                           **/
/*********************************************************************/
//priority_queue<mytimer *, deque<mytimer *>, timerCmp> myTimerQueue;
class TimerQueue {
public:
    // 构造函数
    TimerQueue() {
        myTimerQueue = new priority_queue<mytimer *, deque<mytimer *>, timerCmp>();
    }

    // add_timer
    void add_timer(mytimer *timer) {
        myTimerQueue->push(timer);
    }

    bool is_empty() {
        return myTimerQueue->empty();
    }

    mytimer *gettop() {
        return myTimerQueue->top();
    }

    void deltop() {
        myTimerQueue->pop();
    }


private:
    priority_queue<mytimer *, deque<mytimer *>, timerCmp> *myTimerQueue;
};

#endif //WEBSERVER_V2_0_REQUESTDATA_H
