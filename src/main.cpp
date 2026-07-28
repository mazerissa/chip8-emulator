#include "chip8.hpp"
#include <iostream>
int main()
{
    std::cout << "CHIP-8 Emulator\n\n";

    Chip_8 chip8;

    chip8.initialize();
    
    if (!chip8.loadROM("roms/test.ch8"))
    {
        return 1;
    }

    constexpr int debug_cycles = 20;

    for (int i = 0; i < debug_cycles; ++i)
    {
        chip8.emulateCycle();
    }

    return 0;
}