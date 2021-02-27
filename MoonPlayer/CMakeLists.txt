cmake_minimum_required(VERSION 3.5)

project(MoonPlayer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


file( GLOB header_list *.h  ${CMAKE_CURRENT_SOURCE_DIR}/*.h )
file( GLOB source_list *.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)


add_executable(${PROJECT_NAME} ${header_list} ${source_list} )
target_link_libraries(${PROJECT_NAME} avformat)
target_link_libraries(${PROJECT_NAME} avutil)
target_link_libraries(${PROJECT_NAME} avcodec)
target_link_libraries(${PROJECT_NAME} swscale)
target_link_libraries(${PROJECT_NAME} swresample)
