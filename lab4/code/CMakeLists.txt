cmake_minimum_required(VERSION 3.15)
project(egor_code)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(app
        controller.cpp
        controller.h
        main.cpp
        time_test.cpp
        time_test.h
        mult_matrix.cpp
        mult_matrix.h
        result.txt
        mul_test.cpp
        mul_test.h)
