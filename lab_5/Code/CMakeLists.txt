cmake_minimum_required(VERSION 3.15)
project(code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(code
        main.cpp
        myobject.cpp
        myobject.h
        postprocessing.cpp
        postprocessing.h
        preprocessing.cpp
        preprocessing.h
        processing.cpp
        processing.h
        times_)
