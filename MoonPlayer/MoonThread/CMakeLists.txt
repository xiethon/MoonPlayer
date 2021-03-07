cmake_minimum_required(VERSION 3.5)

project(MoonThread LANGUAGES CXX)

#头文件路径
file( GLOB header_list ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

#源文件路径
file( GLOB source_list ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )

add_library(${PROJECT_NAME} ${header_list} ${source_list})


