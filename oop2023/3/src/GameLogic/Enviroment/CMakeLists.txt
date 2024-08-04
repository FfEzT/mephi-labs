cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_library(Enviroment STATIC source/Enviroment.cpp "source/Database.cpp")

target_include_directories(Enviroment PUBLIC include)
target_link_libraries(Enviroment PUBLIC Informator Subject Coords Engine Mover id_t)
