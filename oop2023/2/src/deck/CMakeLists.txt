cmake_minimum_required(VERSION 3.16)
project(Deck)

set(CMAKE_CXX_STANDARD 20)

add_library(Deck STATIC source/deck.cpp)

target_include_directories(Deck PUBLIC include)
target_link_libraries(Deck Card Utils)
