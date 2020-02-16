cmake_minimum_required(VERSION 3.15)
project(code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(code
        commivoyajer.cpp
        commivoyajer.h
        main.cpp
        matrix.cpp
        matrix.h)
