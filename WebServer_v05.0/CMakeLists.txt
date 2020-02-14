cmake_minimum_required(VERSION 3.15)
project(WebServer_v5_0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(WebServer_v5_0 main.cpp util.cpp util.h epoll.cpp epoll.h requestData.cpp requestData.h threadpool.cpp threadpool.h)