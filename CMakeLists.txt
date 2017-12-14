cmake_minimum_required(VERSION 2.8.12.2)
project(project3_merve_ilik_2015400006_master)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES
        cmake-build-debug/CMakeCache.txt
        CMakeLists.txt
        main.cpp
        Edge.h
        Edge.cpp
        Node.h
        Node.cpp
        Status.h
        Status.cpp
        )

add_executable(project3 ${SOURCE_FILES})