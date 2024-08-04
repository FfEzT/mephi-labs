cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_library(Engine STATIC source/AI.cpp)

target_include_directories(Engine PUBLIC include)
target_link_libraries(Engine PUBLIC Enviroment Coords)
