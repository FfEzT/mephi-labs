cmake_minimum_required(VERSION 3.16)

project(oopprog2)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")



# add_subdirectory(src/vector)

add_subdirectory(src/main)
add_subdirectory(src/card)
add_subdirectory(src/utils)
add_subdirectory(src/deck)
add_subdirectory(src/lib_io)
add_subdirectory(src/dialogue)

# add_subdirectory(src/tests)
# add_subdirectory(dist/gtest)
