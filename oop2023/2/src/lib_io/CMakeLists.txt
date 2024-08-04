cmake_minimum_required(VERSION 3.16)
project(lib_io)

set(CMAKE_CXX_STANDARD 20)

add_library(lib_io INTERFACE)

target_include_directories(lib_io INTERFACE include)