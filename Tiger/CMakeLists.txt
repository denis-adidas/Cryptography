cmake_minimum_required(VERSION 3.27)
project(lab04)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab04 main.cpp
        tiger.cpp
        tiger.hpp
        sboxes.cpp)
