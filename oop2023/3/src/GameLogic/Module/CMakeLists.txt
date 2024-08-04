cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_library(Module STATIC source/BasicSensor.cpp)

target_include_directories(Module PUBLIC include)
target_link_libraries(Module PUBLIC Coords id_t)