cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_library(Object STATIC source/IPlatform.cpp "source/ICommandPlatform.cpp" "source/BasicCommandPlatform.cpp" "../id_t/include/IdTexture.h")

target_include_directories(Object PUBLIC include)
target_link_libraries(Object PUBLIC Module)