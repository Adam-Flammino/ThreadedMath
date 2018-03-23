cmake_minimum_required(VERSION 3.9)
project(threadedMath C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
add_executable(threadedMath main.c)
