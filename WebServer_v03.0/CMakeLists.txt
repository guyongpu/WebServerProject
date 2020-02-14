cmake_minimum_required(VERSION 3.15)
project(WebServer_v4_0)

set(CMAKE_CXX_STANDARD 14)

add_executable(WebServer_v4_0 main.cpp http_conn.cpp http_conn.h locker.h threadpool.h main.cpp threadpool.h locker.h http_conn.cpp http_conn.h)