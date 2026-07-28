#include "chip8.hpp"

#include <algorithm>
#include <format>
#include <iomanip>
#include <iostream>
#include <fstream>

void Chip_8::initialize()
{
    pc = 0x200;
    I = 0;
    sp = 0;

    std::fill(std::begin(memory), std::end(memory), 0);
    std::fill(std::begin(V), std::end(V), 0);
    std::fill(std::begin(stack), std::end(stack), 0);

}

bool Chip_8::loadROM(const std::string& filename)
{
    std::ifstream rom(filename, std::ios::binary);

    if (!rom.is_open())
    {
        std::cerr << "Failed to open ROM: " << filename << '\n';
        return false;
    }

    rom.seekg(0, std::ios::end);
    const std::streamsize size = rom.tellg();
    rom.seekg(0, std::ios::beg);

    if (size <= 0)
    {
        std::cerr << "ROM is empty.\n";
        return false;
    }

    constexpr std::size_t start = 0x200;

    if (static_cast<std::size_t>(size) > memory.size() - start)
    {
        std::cerr << "ROM is too large.\n";
        return false;
    }

    rom.read(reinterpret_cast<char*>(memory.data() + start), size);

    std::cout << "Loaded ROM: "
              << filename
              << " ("
              << size
              << " bytes)\n";

    return true;
}

void Chip_8::emulateCycle()
{

    const uint16_t opcode = (memory[pc] << 8) | memory[pc + 1];

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