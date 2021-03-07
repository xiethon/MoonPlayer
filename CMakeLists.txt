cmake_minimum_required(VERSION 3.5)

project ( MoonPlayer )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${PROJECT_SOURCE_DIR}/bin)

link_directories( ${CMAKE_CURRENT_SOURCE_DIR}/3rdPart/ffmpeg/lib)

add_subdirectory (MoonPlayer)
add_subdirectory (MoonPlayerClient)
