//
// Created by yongpu on 2/4/20.
//

#ifndef WEBSERVER_V9_0_LOGGING_H
#define WEBSERVER_V9_0_LOGGING_H

#include "LogStream.h"
#include <pthread.h>
#include <string.h>
#include <string>
#include <stdio.h>

class AsyncLogging;

class Logger
{
public:
    ~Logger();
    Logger(const char *fileName, int line);
    LogStream& stream() { return impl_.stream_; }

private:
    class Impl
    {
    public:
        Impl(const char *fileName, int line);
        void formatTime();

        LogStream stream_;
        int line_;
        std::string basename_;
    };
    Impl impl_;
};

#define LOG Logger(__FILE__, __LINE__).stream()

#endif //WEBSERVER_V9_0_LOGGING_H
