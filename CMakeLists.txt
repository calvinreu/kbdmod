cmake_minimum_required(VERSION 3.10)

project(keyboard_modify VERSION 0.0.1)
set_target_properties(${SRC_FILES} PROPERTIES
VERSION ${PROJECT_VERSION}
SOVERSION ${PROJECT_VERSION_MAJOR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
#search source dir
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(source ${SRC_FILES})


add_executable(keyboard_modify.bin src/main.cpp)

TARGET_LINK_LIBRARIES(keyboard_modify.bin source jsoncpp)
