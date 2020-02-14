//
// Created by yongpu on 2/4/20.
//

#ifndef WEBSERVER_V9_0_LOGFILE_H
#define WEBSERVER_V9_0_LOGFILE_H


#include "FileUtil.h"
#include "MutexLock.h"
#include "noncopyable.h"
#include <memory>
#include <string>

class LogFile : noncopyable
{
public:
    LogFile(const std::string& basename, int flushEveryN = 1024);
    ~LogFile();

    void append(const char* logline, int len);
    void flush();
    bool rollFile();

private:
    void append_unlocked(const char* logline, int len);

    const std::string basename_;
    const int flushEveryN_;

    int count_;
    std::unique_ptr<MutexLock> mutex_;
    std::unique_ptr<AppendFile> file_;
};


#endif //WEBSERVER_V9_0_LOGFILE_H
