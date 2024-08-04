cmake_minimum_required(VERSION 3.16)
project(main)

set(CMAKE_CXX_STANDARD 20)

add_executable(main_ok source/main.cpp)

target_link_libraries(main_ok Card Deck Dialogue)
