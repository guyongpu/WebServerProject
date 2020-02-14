#include "LogFile.h"
#include "FileUtil.h"
#include <assert.h>
#include <stdio.h>
#include <time.h>

using namespace std;


LogFile::LogFile(const string &basename, int flushEveryN)
        : basename_(basename),
          flushEveryN_(flushEveryN),
          count_(0),
          mutex_(new MutexLock) {
    //assert(basename.find('/') >= 0);
    file_.reset(new AppendFile(basename));
}

LogFile::~LogFile() {}

void LogFile::append(const char *logline, int len) {
    MutexLockGuard lock(*mutex_);
    append_unlocked(logline, len);
}

void LogFile::flush() {
    /* 加锁操作，防止线程不安全，保证同一时刻不会执行多个写操作 */
    MutexLockGuard lock(*mutex_);
    file_->flush();
}

void LogFile::append_unlocked(const char *logline, int len) {
    file_->append(logline, len); /* 将logline写入到文件中 */
    ++count_;
    if (count_ >= flushEveryN_) {
        count_ = 0;
        file_->flush();
    }
}