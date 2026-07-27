#include "chip8.hpp"

#include <algorithm>
#include <format>
#include <iomanip>
#include <iostream>

void Chip_8::initialize()
{
    pc = 0x200;
    I = 0;
    sp = 0;


    std::fill(std::begin(memory), std::end(memory), 0);
    std::fill(std::begin(V), std::end(V), 0);
    std::fill(std::begin(stack), std::end(stack), 0);


    memory[0x200] = 0x60; memory[0x201] = 0x0A; 
    memory[0x202] = 0x61; memory[0x203] = 0x05; 
    memory[0x204] = 0x70; memory[0x205] = 0x05; 

    std::cout << "Memory test: 0x" << std::hex << static_cast<int>(memory[0x200]) 
              << " 0x" << static_cast<int>(memory[0x201]) << "\n";
}

void Chip_8::emulateCycle()
{

    const uint16_t opcode = (memory[pc] << 8) | memory[pc + 1];

    // Decode common nibbles/values up front
    const uint8_t x  = (opcode & 0x0F00) >> 8; 
    const uint8_t nn =  opcode & 0x00FF;      

    std::cout << "PC: 0x" << std::hex << pc 
              << " | Opcode: 0x" << opcode << "\n";

    switch (opcode & 0xF000)
    {
        case 0x6000: 
            V[x] = nn;
            std::cout << "V" << static_cast<int>(x) << " = " << static_cast<int>(V[x]) << "\n";
            break;

        case 0x7000: 
            V[x] += nn;
            std::cout << "V" << static_cast<int>(x) << " += " << static_cast<int>(nn) << "\n";
            break;

        default:
            std::cout << "Unknown opcode: 0x" << std::hex << opcode << "\n";
            break;
    }


    pc += 2;
}