cmake_minimum_required(VERSION 3.15)
project(code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(code
        controller.cpp
        controller.h
        main.cpp
        mul_test.cpp
        mul_test.h
        mult_matrix.cpp
        mult_matrix.h
        time_test.cpp
        time_test.h)
