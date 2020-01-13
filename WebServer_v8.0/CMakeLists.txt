cmake_minimum_required(VERSION 3.15)
project(WebServer_v8_0)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(WebServer_v8_0 main.cpp util.cpp util.h condition.hpp nocopyable.hpp mutexLock.hpp Epoll.cpp Epoll.h timer.cpp timer.h requestData.cpp requestData.h threadpool.cpp threadpool.h)