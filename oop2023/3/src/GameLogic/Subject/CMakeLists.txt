cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_library(Subject INTERFACE)

target_include_directories(Subject INTERFACE include)
target_link_libraries(Subject INTERFACE Object Coords)