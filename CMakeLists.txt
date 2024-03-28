cmake_minimum_required(VERSION 3.27)
project(345Project)
set(CMAKE_CXX_STANDARD 17)

include_directories(src)
add_executable(345Project
        MapGeneration.cpp
        MapGeneration.h
)

add_executable(TestExecutable
)
