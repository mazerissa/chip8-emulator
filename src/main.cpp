#include "chip8.hpp"

#include <iostream>

int main()
{
    std::cout << "CHIP-8 Emulator Initializing...\n\n";

    Chip_8 chip8;
    chip8.initialize();

    constexpr int debug_cycles = 10;

    for (int i = 0; i < debug_cycles; ++i)
    {
        chip8.emulateCycle();
    }

    return 0;
}