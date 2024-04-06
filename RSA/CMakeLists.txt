cmake_minimum_required(VERSION 3.26.4)
project(RSA)

set(Boost_INCLUDE_DIR c:/mingw/mingw/include/)
set(Boost_LIBRARY_DIR c:/mingw/mingw/lib/)

find_package(Boost COMPONENTS system filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 17)

add_executable(RSA
        main.cpp
        RSA.hpp
        RSA.cpp
        sha2.h)
