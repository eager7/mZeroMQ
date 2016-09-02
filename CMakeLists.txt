cmake_minimum_required(VERSION 3.5)
project(mZeroMQ)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES proxy/msgqueue.c.cpp)
add_executable(mZeroMQ ${SOURCE_FILES})