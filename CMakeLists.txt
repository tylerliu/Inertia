cmake_minimum_required(VERSION 2.8)
project(Inertia)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -std=c11")

set(SOURCE_FILES src/main.c
        src/Instr_set.c
        src/Instr_set.h
        src/Execution.c
        src/Execution.h
        src/RegMem.c
        src/regMem.h)
add_executable(Inertia ${SOURCE_FILES})
