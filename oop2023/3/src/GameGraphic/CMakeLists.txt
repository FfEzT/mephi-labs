cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_library(gameGraphic STATIC "source/GameGraphic.cpp" "source/Builder.cpp")
target_include_directories(gameGraphic PUBLIC include)

target_link_libraries(gameGraphic PUBLIC sfml-graphics Enviroment Engine)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/materials/picture/commandModule.png
			   ${CMAKE_CURRENT_BINARY_DIR}/materials/picture/commandModule.png
			   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/materials/picture/generator.png
			   ${CMAKE_CURRENT_BINARY_DIR}/materials/picture/generator.png
			   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/materials/picture/sensor.png
			   ${CMAKE_CURRENT_BINARY_DIR}/materials/picture/sensor.png
			   COPYONLY)


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/materials/picture/grid.png
			   ${CMAKE_CURRENT_BINARY_DIR}/materials/picture/grid.png
			   COPYONLY)


configure_file("${CMAKE_CURRENT_SOURCE_DIR}/materials/picture/Command platform.png"
			   "${CMAKE_CURRENT_BINARY_DIR}/materials/picture/Command platform.png"
			   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/materials/picture/Platform.png
			   ${CMAKE_CURRENT_BINARY_DIR}/materials/picture/Platform.png
			   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/materials/picture/Let.png
			   ${CMAKE_CURRENT_BINARY_DIR}/materials/picture/Let.png
			   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/materials/picture/Interest.png
			   ${CMAKE_CURRENT_BINARY_DIR}/materials/picture/Interest.png
			   COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/materials/picture/No object.png"
			   "${CMAKE_CURRENT_BINARY_DIR}/materials/picture/No object.png"
			   COPYONLY)


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/materials/map.txt
			   ${CMAKE_CURRENT_BINARY_DIR}/materials/map.txt
			   COPYONLY)