cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(main main.cpp)

#function(copy_files_with_substitution SOURCE_DIR DEST_DIR)
#    file(GLOB files "${SOURCE_DIR}/*")
#    foreach(file ${files})
#        get_filename_component(filename ${file} NAME)
#        set(dest ${DEST_DIR}/${filename})
#        configure_file(${file} ${dest} @ONLY)
#    endforeach()
#endfunction()

#copy_files_with_substitution(${CMAKE_CURRENT_SOURCE_DIR}/materials/picture ${CMAKE_CURRENT_BINARY_DIR}/materials/picture)



target_link_libraries(main gameGraphic)
