cmake_minimum_required(VERSION 3.5)
project(ansi)

SET (CMAKE_CXX_STANDARD 14)

add_executable(interactive-ansi-escape
    src/interactive-ansi-escape.cpp
    src/ansi.cpp)

target_include_directories(interactive-ansi-escape PRIVATE src/)


