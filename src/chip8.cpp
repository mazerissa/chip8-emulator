#include "chip8.hpp" //importing chip8 class

#include <cstring>
#include <iostream>

void Chip_8::initialize() //chip initialization
{
    pc = 0x200; // Reset program counter

    I = 0; // Reset index register

    sp = 0; // Reset stack pointer

    memset(memory, 0, sizeof(memory)); // Clear mem

    memset(V, 0, sizeof(V)); // Clear registers
  
    memset(stack, 0, sizeof(stack)); // Clear stack
}


void Chip_8::emulateCycle() //run one cycle of CPU
{
    if (pc >= 4095) // safty net
    {
        std::cout << "end of memory\n";
        return;
    }

    std::cout << "PC: " << std::hex << pc << "\n"; // print PC

    uint16_t opcode = memory[pc] << 8 | memory[pc + 1]; // get opcode

    std::cout << "Opcode: " << std::hex << opcode << "\n"; // print opcode

    pc += 2; // Increment program counter
}