#include "FileUtil.h"
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

/* 构造函数，打开文件，设置缓冲区 */
AppendFile::AppendFile(string filename) {
    fp_ = fopen(filename.c_str(), "a");
    // 用户提供缓冲区
    setbuffer(fp_, buffer_, sizeof buffer_);
}

/* 析构函数，关闭文件 */
AppendFile::~AppendFile() {
    fclose(fp_);
}

void AppendFile::append(const char *logline, const size_t len) {
    size_t n = this->write(logline, len);
    size_t remain = len - n;
    while (remain > 0) {
        size_t x = this->write(logline + n, remain);
        if (x == 0) {
            int err = ferror(fp_);
            if (err)
                fprintf(stderr, "AppendFile::append() failed !\n");
            break;
        }
        n += x;
        remain = len - n;
    }
}

void AppendFile::flush() {
    // 刷新缓冲区，强制写入到fp的文件中
    fflush(fp_);
}

/* 将字符串logline写入到文件中 */
size_t AppendFile::write(const char *logline, size_t len) {
    return fwrite_unlocked(logline, 1, len, fp_);
}