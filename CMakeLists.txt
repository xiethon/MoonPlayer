cmake_minimum_required(VERSION 3.5)

project ( MoonPlayer )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${PROJECT_SOURCE_DIR}/bin)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include/ffmpeg)
link_directories( ${CMAKE_CURRENT_SOURCE_DIR}/lib/ffmpeg)
add_subdirectory (MoonPlayer)
