cmake_minimum_required(VERSION 3.20)

project(CHIP8)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

add_executable(chip8
    src/main.cpp
    src/chip8.cpp
    src/renderer.cpp
)

target_include_directories(chip8 PRIVATE src)

target_link_libraries(chip8 PRIVATE
    SDL2::SDL2
)