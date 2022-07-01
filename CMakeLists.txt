cmake_minimum_required(VERSION 3.10)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB_RECURSE source src/*.cpp)
add_library(source ${source})
#add verison to source files
project(keyboard_modify VERSION 0.0.1)
set_target_properties(source PROPERTIES
VERSION ${PROJECT_VERSION}
SOVERSION ${PROJECT_VERSION_MAJOR})

add_executable(keyboard_modify.bin src/main.cpp)

TARGET_LINK_LIBRARIES(keyboard_modify.bin source)
