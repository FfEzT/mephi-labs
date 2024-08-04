cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_subdirectory(id_t)
add_subdirectory(Coords)
add_subdirectory(Engine)
add_subdirectory(Enviroment)
add_subdirectory(Informator)
add_subdirectory(Module)
add_subdirectory(Object)
add_subdirectory(Mover)
add_subdirectory(Subject)