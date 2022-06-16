cmake_minimum_required(VERSION 3.10)

project(keyboard-configurator VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB_RECURSE source src/*.cpp)

add_library(source STATIC ${source})

# test file for gbd DEBUGER
add_executable(test.out test.cpp)
# installation file
add_executable(input-interception main.cpp)

TARGET_LINK_LIBRARIES(input-interception source)
TARGET_LINK_LIBRARIES(test.out source)
