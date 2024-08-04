cmake_minimum_required(VERSION 3.16)
project(Dialogue)

set(CMAKE_CXX_STANDARD 20)

add_library(Dialogue STATIC source/dialog.cpp)

target_include_directories(Dialogue PUBLIC include)
target_link_libraries(Dialogue lib_io Deck)
