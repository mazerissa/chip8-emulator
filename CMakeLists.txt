cmake_minimum_required(VERSION 3.20)

project(CHIP8)

set(CMAKE_CXX_STANDARD 17)

add_executable(
    chip8
    src/main.cpp
    src/chip8.cpp
)