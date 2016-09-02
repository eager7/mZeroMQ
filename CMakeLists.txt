cmake_minimum_required(VERSION 3.6)
project(mZeroMQ)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(
        zeromq-4.1.5/include
        zeromq-4.1.5/src
)
AUX_SOURCE_DIRECTORY(zeromq-4.1.5/ DIRSRC)
set(SOURCE_FILES zeromq-4.1.5/src/*.cpp)
add_executable(mZeroMQ ${SOURCE_FILES} ${DIRSRC)