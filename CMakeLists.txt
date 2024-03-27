cmake_minimum_required(VERSION 3.27)
project(345Project)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(catchTests)

#cpp files only
add_executable(345Project
        src/main.cpp
        src/Static/Functions.cpp
        src/Static/Dice.cpp
        src/Components/Character.cpp
        

)

#[[
add_executable(TestExecutable
        

)
]]
