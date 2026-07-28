cmake_minimum_required(VERSION 3.10)
project(chip8)

set(CMAKE_CXX_STANDARD 20)

add_executable(chip8
    src/main.cpp
    src/chip8.cpp
    src/renderer.cpp
    src/keyboard.cpp
)

# 2. Find MSYS2's SDL2 library
find_package(SDL2 REQUIRED)

# 3. Link SDL2 to your emulator
target_link_libraries(chip8 PRIVATE SDL2::SDL2main SDL2::SDL2)