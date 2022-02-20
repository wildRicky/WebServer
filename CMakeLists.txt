cmake_minimum_required( VERSION 2.8 )

set( CMAKE_CXX_FLAGS "-std=c++11" )
set( CMAKE_CXX_FLAGS "-std=c++20" )
set( CMAKE_CXX_FLAGS "-pthread" )
add_definitions("-g")

PROJECT(webserver)
MESSAGE(STATUS "Project: SERVER") #打印相关消息消息
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

aux_source_directory (. SRC_LIST)
include_directories (.)


add_executable(${PROJECT_NAME} ${SRC_LIST})

