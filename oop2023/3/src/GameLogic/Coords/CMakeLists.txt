cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")


add_library(Coords STATIC source/Coords.cpp source/Direction.cpp)
target_include_directories(Coords PUBLIC include)
