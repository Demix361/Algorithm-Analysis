cmake_minimum_required(VERSION 3.15)
project(Code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Code
        conveyor.cpp
        conveyor.h
        elem.h
        main.cpp)
