cmake_minimum_required(VERSION 3.16)   
project(Tests)

set(CMAKE_CXX_STANDARD 20)

add_executable (testing source/test.cpp)

target_link_libraries(testing Card Deck Vector gtest gtest_main)