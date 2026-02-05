cmake_minimum_required(VERSION 3.5)
project(ansi)

SET (CMAKE_CXX_STANDARD 14)

add_executable(ansi-escape
    src/ansi-escape.cpp
    src/environment.cpp
    src/ansi.cpp)

target_include_directories(ansi-escape PRIVATE src/)


