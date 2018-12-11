cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

project(basic)

add_executable(basic basic.cpp)

project(advanced)

add_executable(advanced advanced.cpp)