cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_subdirectory(GameLogic)
add_subdirectory(GameGraphic)
add_subdirectory(dist)
add_subdirectory(exec)

add_compile_options(--coverage)
add_link_options(--coverage)