cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(the-sorting)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

#
# My Project
#
add_subdirectory(sorting-algorithm)


enable_testing()
add_subdirectory(test)
