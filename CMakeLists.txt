cmake_minimum_required(VERSION 3.27)
project(345Project)
set(CMAKE_CXX_STANDARD 17)

include_directories(src)
add_executable(345Project
)

add_executable(TestExecutable
)

add_subdirectory(external/catch2)
target_link_libraries(TestExecutable PRIVATE Catch2::Catch2WithMain)