cmake_minimum_required(VERSION 3.8)
project(DES)

set(CMAKE_CXX_STANDARD 11)
set(TEST test.cpp)

set(SOURCE_FILES main.cpp)
add_executable(DES ${SOURCE_FILES})
add_executable(TEST test.cpp)