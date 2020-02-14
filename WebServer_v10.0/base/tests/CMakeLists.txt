cmake_minimum_required(VERSION 3.15)
project(LogSystem)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


add_executable(LogSystem LoggingTest.cpp
        ../AsyncLogging.h ../AsyncLogging.cpp
        ../Condition.h
        ../CountDownLatch.h ../CountDownLatch.cpp
        ../CurrentThread.h
        ../FileUtil.h ../FileUtil.cpp
        ../LogFile.h ../LogFile.cpp
        ../Logging.h ../Logging.cpp
        ../LogStream.h ../LogStream.cpp
        ../MutexLock.h
        ../noncopyable.h
        ../Thread.h ../Thread.cpp)