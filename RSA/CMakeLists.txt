cmake_minimum_required(VERSION 3.27.8)
project(RSA)

set(CMAKE_CXX_STANDARD 17)

add_executable(RSA main.cpp
        RSA.cpp
        RSA.hpp
        sha2.h)
