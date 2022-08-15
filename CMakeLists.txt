cmake_minimum_required(VERSION 3.10)

project(kbdmod)

# Check if debug
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  message(STATUS "Debug build")
  add_compile_definitions(DEBUG TRUE)
endif()



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
#search source dir
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(source ${SRC_FILES})


add_executable(kbdmod.bin src/main.cpp)

TARGET_LINK_LIBRARIES(kbdmod.bin source yaml-cpp evdev pthread)
