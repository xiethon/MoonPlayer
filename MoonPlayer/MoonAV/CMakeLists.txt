cmake_minimum_required(VERSION 3.5)

project(MoonAV LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/../../3rdPart/ffmpeg/include)

#头文件路径
file( GLOB header_list *.h )

#源文件路径
file( GLOB source_list *.cpp )

add_executable(${PROJECT_NAME} ${header_list} ${source_list})

#链接 ffmpeg
target_link_libraries(${PROJECT_NAME} avformat)
target_link_libraries(${PROJECT_NAME} avutil)
target_link_libraries(${PROJECT_NAME} avcodec)
target_link_libraries(${PROJECT_NAME} swscale)
target_link_libraries(${PROJECT_NAME} swresample)
