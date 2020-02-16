cmake_minimum_required(VERSION 3.15)
project(egor_code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(egor_code
    aco.cpp
    aco.h
    controller.cpp
    controller.h
    main.cpp
    main_t.cpp
    matrix.h
    print.cpp
    print.h
    res.cpp
    res.h
    research.cpp
    test.cpp
    test_.cpp
    test_.h
    test_runner.h
    time.cpp
    total_search.cpp
    total_search.h)
