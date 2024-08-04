cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# TODE rename to utils

add_library(id_t INTERFACE)

target_include_directories(id_t INTERFACE include)
