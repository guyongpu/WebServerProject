cmake_minimum_required(VERSION 3.15)
project(WebServer_10_0)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(WebServer_10_0 main.cpp Util.cpp Util.h Timer.cpp Timer.h ThreadPool.cpp ThreadPool.h Server.cpp Server.h HttpData.cpp HttpData.h EventLoop.cpp EventLoop.h Epoll.cpp Epoll.h Channel.cpp Channel.h EventLoopThread.cpp EventLoopThread.h EventLoopThreadPool.cpp EventLoopThreadPool.h)

