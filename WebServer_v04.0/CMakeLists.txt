cmake_minimum_required(VERSION 3.15)
project(WebServer_v4_0)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(WebServer_v4_0 main.cpp util.cpp util.h requestData.cpp requestData.h epoll.cpp epoll.h threadpool.cpp threadpool.h)