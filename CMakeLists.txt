cmake_minimum_required(VERSION 3.10)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#add verison to source files
project(keyboard_modify VERSION 0.0.1)

add_executable(keyboard_modify.bin src/main.cpp)
