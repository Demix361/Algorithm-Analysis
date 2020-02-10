cmake_minimum_required(VERSION 3.15)
project(egor_code)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(egor_code
        controller.cpp
        controller.h
        main.cpp
        metering.cpp
        metering.h
        mult_matrix.cpp
        mult_matrix.h
        result.txt
        test.cpp
        test.h)
