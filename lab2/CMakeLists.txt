cmake_minimum_required(VERSION 3.24)

project(lab2 C CXX)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT lab2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

add_executable(lab2 main.c source/func.c)
