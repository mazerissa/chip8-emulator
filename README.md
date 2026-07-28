# CHIP-8 Emulator

## Abstract

CHIP-8 virtual machine written in C++. The purpose of this project is to study computer architecture concepts, emulator development, instruction decoding, memory management, graphics rendering, and input handling.

---

# Features

Current implemented features:

- CHIP-8 CPU emulation
- 4 KB memory system
- 16 general-purpose registers (V0-VF)
- Index register (I)
- Program counter and stack handling
- Delay and sound timers
- CHIP-8 keypad input system
- SDL2 graphics renderer
- ROM loading system
- Sprite drawing
- Collision detection
- Basic sound timer support

Supported instructions include:

- Flow control instructions
- Register manipulation
- Arithmetic operations
- Bitwise operations
- Conditional execution
- Memory operations
- Sprite rendering
- Keyboard input instructions

---

# Requirements

## Software Requirements

The following software is required:

- C++20 compatible compiler
- CMake 3.20 or newer
- SDL2 development libraries
- Git

Supported platforms:

- Windows
- Linux
- macOS

---

# Project Structure

```

CHIP-8 Emulator/

├── src/
│   ├── main.cpp
│   ├── chip8.cpp
│   ├── chip8.hpp
│   ├── renderer.cpp
│   ├── renderer.hpp
│   ├── keyboard.cpp
│   └── keyboard.hpp
│
├── roms/
│   └── game files (.ch8)
│
├── build/
│
├── CMakeLists.txt
└── README.md

```

---

# Installation

## 1. Clone the repository

```

git clone https://github.com/mazerissa/chip8-emulator

```

Navigate into the project directory:

```

cd CHIP-8-Emulator

```

---

## 2. Install SDL2

SDL2 must be installed before building the emulator.

For Windows using MSYS2:

```

pacman -S mingw-w64-ucrt-x86-SDL2

```

For Linux:

```

sudo apt install libsdl2-dev

```

---

## 3. Create build directory

From the project root:

```

mkdir build
cd build

```

---

## 4. Configure the project

Using CMake:

```

cmake .. -G "MinGW Makefiles"

```

For other platforms, the default CMake generator can be used:

```

cmake ..

```

---

## 5. Compile

Build the project:

```

cmake --build .

```

After successful compilation, the executable will be generated:

```

chip8.exe

```

---

# Running the Emulator

Return to the project root:

```

cd ..

```

Run:

```

./build/chip8.exe

```

The emulator will load the configured ROM file and start execution.

---

# Adding Games

The emulator requires CHIP-8 ROM files with the `.ch8` extension.

Create a ROM directory:

```

roms/

```

Place your games inside:

```

roms/
├── pong.ch8
├── tetris.ch8
├── invaders.ch8
└── .......ect

````

To select a game, edit `main.cpp`:

```cpp
chip8.loadROM("roms/pong.ch8");
````

Replace the filename with the desired ROM.

---

# ROM Credits

The CHIP-8 games used for testing and demonstration purposes are provided by the CHIP-8 community.

ROM collection source:

[kripod/chip8-roms](https://github.com/kripod/chip8-roms)


All credit for the original game programs belongs to their respective authors and contributors.

This emulator project does not claim ownership of the included ROM files.

---

# Controls

The CHIP-8 keypad is mapped to the keyboard as follows:

```
CHIP-8       Keyboard

1 2 3 C      1 2 3 4

4 5 6 D      Q W E R

7 8 9 E      A S D F

A 0 B F      Z X C V
```

The Escape key exits the emulator.

