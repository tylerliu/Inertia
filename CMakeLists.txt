cmake_minimum_required(VERSION 2.8)
project(Inertia)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -std=c11")

set(SOURCE_FILES src/main.c)
add_executable(Inertia ${SOURCE_FILES})
