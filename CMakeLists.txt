cmake_minimum_required(VERSION 2.8)
project(Inertia)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -std=c11")

aux_source_directory(src/ SOURCE_FILES)
add_executable(Inertia ${SOURCE_FILES})
