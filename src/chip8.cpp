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


void Chip_8::emulateCycle()
{
    std::cout << "PC: " << pc << "\n";

    uint16_t opcode = memory[pc] << 8 | memory[pc + 1];

    std::cout << "Opcode read\n";

    pc += 2;
}