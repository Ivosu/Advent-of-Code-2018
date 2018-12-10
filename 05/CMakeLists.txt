cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -pedantic -Wall")
project(05_basic)

add_executable(05_basic basic.cpp)

project(05_advanced)

add_executable(05_advanced advanced.cpp)