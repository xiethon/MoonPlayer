cmake_minimum_required(VERSION 3.5)

project(MoonPlayerClient LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS  Widgets   REQUIRED)


file( 
	GLOB header_list *.h  
	${CMAKE_CURRENT_SOURCE_DIR}/*.h 
)

file( 
	GLOB source_list *.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

file( GLOB shader_list ${CMAKE_CURRENT_SOURCE_DIR}/player.vert   ${CMAKE_CURRENT_SOURCE_DIR}/player.frag)
file( GLOB ui_list *.ui ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
file( GLOB qrc_list *.qrc ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)

qt5_wrap_ui( generated_ui_list ${ui_list} )
qt5_add_resources( generated_qrc_list ${qrc_list} )


add_executable(${PROJECT_NAME} ${header_list} ${source_list} ${generated_ui_list} ${generated_qrc_list} ${shader_list} )

#����Qt lib
target_link_libraries(${PROJECT_NAME}  Qt5::Widgets)
