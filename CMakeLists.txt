cmake_minimum_required(VERSION 3.6)
project(Labs)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++11")

set(SOURCE_FILES nlab4.cpp nlab4.cpp)
add_executable(Labs ${SOURCE_FILES})