cmake_minimum_required(VERSION 3.25)
project(KaithanOS)

set(CMAKE_CXX_STANDARD 14)

include_directories(containers)

add_executable(KaithanOS
        containers/Vector.cpp
        containers/Vector.h containers/Heap.h)
