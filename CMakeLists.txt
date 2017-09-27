cmake_minimum_required(VERSION 3.8)
project(DES)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
set(SOURCE_FILES test.cpp test.cpp)
add_executable(DES ${SOURCE_FILES})
add_executable(DES test.cpp test.cpp)
