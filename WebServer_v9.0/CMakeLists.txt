cmake_minimum_required(VERSION 3.15)
project(WebServer_v9_0)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(WebServer_v9_0 main.cpp util.cpp util.h timer.cpp threadpool.h timer.h threadpool.cpp Thread.h Thread.cpp requestData.h requestData.cpp noncopyable.h MutexLock.h Condition.h epoll.h epoll.cpp AsyncLogging.h AsyncLogging.cpp CountDownLatch.cpp CountDownLatch.h LogStream.cpp LogStream.h Logging.cpp Logging.h LogFile.cpp LogFile.h FileUtil.cpp FileUtil.h config.h)