cmake_minimum_required(VERSION 3.15)
project(WebServer_v7_0)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(WebServer_v7_0 main.cpp util.cpp util.h nocopyable.hpp mutexLock.hpp Epoll.cpp Epoll.h requestData.cpp requestData.h timer.cpp timer.h threadpool.cpp threadpool.h)