cmake_minimum_required(VERSION 3.16)
project(Utils)

set(CMAKE_CXX_STANDARD 20)

add_library(Utils INTERFACE)

target_include_directories(Utils INTERFACE include)