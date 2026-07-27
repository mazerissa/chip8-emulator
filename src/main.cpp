#include <iostream> // lib for printing shit

#include "chip8.hpp" // import of cpu specs


int main() // start of the work
{
    Chip_8 chip8; // from blueprint to object

    chip8.initialize(); // initialization of da cpu

    std::cout << "CHIP-8 emulator\n"; // printing this 

    while (true) // loop that runs the cpu
    {
        chip8.emulateCycle();
    }

    return 0;
}