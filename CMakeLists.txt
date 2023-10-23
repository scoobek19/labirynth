cmake_minimum_required(VERSION 3.20)
project(jimp_lmp8 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_SOURCE_DIR})

add_executable(miniproj3 edges_lib.c file_manager.c labyrinth_manager.c matrix_manager.c search.c)
