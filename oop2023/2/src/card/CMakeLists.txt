cmake_minimum_required(VERSION 3.16)
project(Card)

set(CMAKE_CXX_STANDARD 20)

add_library(Card STATIC source/card.cpp)

target_include_directories(Card PUBLIC include)
target_link_libraries(Card Utils)
