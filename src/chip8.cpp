#include "chip8.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>


const uint8_t fontset[80] =
{
    0xF0,0x90,0x90,0x90,0xF0, // 0
    0x20,0x60,0x20,0x20,0x70, // 1
    0xF0,0x10,0xF0,0x80,0xF0, // 2
    0xF0,0x10,0xF0,0x10,0xF0, // 3
    0x90,0x90,0xF0,0x10,0x10, // 4
    0xF0,0x80,0xF0,0x10,0xF0, // 5
    0xF0,0x80,0xF0,0x90,0xF0, // 6
    0xF0,0x10,0x20,0x40,0x40, // 7
    0xF0,0x90,0xF0,0x90,0xF0, // 8
    0xF0,0x90,0xF0,0x10,0xF0, // 9
    0xF0,0x90,0xF0,0x90,0x90, // A
    0xE0,0x90,0xE0,0x90,0xE0, // B
    0xF0,0x80,0x80,0x80,0xF0, // C
    0xE0,0x90,0x90,0x90,0xE0, // D
    0xF0,0x80,0xF0,0x80,0xF0, // E
    0xF0,0x80,0xF0,0x80,0x80  // F
};


void Chip_8::initialize()
{
    pc = 0x200;
    I = 0;
    sp = 0;

    delay_timer = 0;
    sound_timer = 0;

    drawFlag = false;


    std::fill(memory.begin(), memory.end(), 0);
    std::fill(V.begin(), V.end(), 0);
    std::fill(stack.begin(), stack.end(), 0);
    std::fill(display.begin(), display.end(), 0);
    std::fill(keypad.begin(), keypad.end(), 0);


    loadFontset();
}



void Chip_8::loadFontset()
{
    for(int i = 0; i < 80; i++)
    {
        memory[0x50 + i] = fontset[i];
    }
}



bool Chip_8::loadROM(const std::string& filename)
{
    const std::vector<std::string> candidates = {
        filename,
        "../" + filename,
        "./" + filename,
        "roms/" + filename,
        "../roms/" + filename
    };

    std::ifstream rom;
    std::string resolvedPath;

    for (const auto& candidate : candidates)
    {
        rom.open(candidate, std::ios::binary | std::ios::ate);
        if (rom.is_open())
        {
            resolvedPath = candidate;
            break;
        }
    }

    if (!rom.is_open())
    {
        std::cerr << "Failed to open ROM: " << filename << "\n";
        return false;
    }


    std::streamsize size = rom.tellg();

    rom.seekg(0, std::ios::beg);


    if(size > (memory.size() - 0x200))
    {
        std::cerr << "ROM too large\n";
        return false;
    }


    rom.read(
        reinterpret_cast<char*>(memory.data() + 0x200),
        size
    );


    std::cout << "Loaded ROM: "
              << resolvedPath
              << " ("
              << size
              << " bytes)\n";


    return true;
}




void Chip_8::emulateCycle()
{
    if (pc >= memory.size() - 1)
    {
        std::cerr << "PC out of bounds\n";
        return;
    }

    uint16_t opcode =
        (memory[pc] << 8) |
        memory[pc + 1];


    uint16_t nnn = opcode & 0x0FFF;

    uint8_t nn = opcode & 0x00FF;

    uint8_t n = opcode & 0x000F;

    uint8_t x = (opcode & 0x0F00) >> 8;

    uint8_t y = (opcode & 0x00F0) >> 4;



    pc += 2;



    switch(opcode & 0xF000)
    {


    case 0x0000:

        if(opcode == 0x00E0)
        {
            std::fill(display.begin(), display.end(), 0);
            drawFlag = true;
        }

        else if(opcode == 0x00EE)
        {
            sp--;
            pc = stack[sp];
        }

        break;



    case 0x1000:

        pc = nnn;

        break;



    case 0x2000:

        stack[sp] = pc;
        sp++;

        pc = nnn;

        break;



    case 0x3000:

        if(V[x] == nn)
            pc += 2;

        break;



    case 0x4000:

        if(V[x] != nn)
            pc += 2;

        break;



    case 0x6000:

        V[x] = nn;

        break;



    case 0x7000:

        V[x] += nn;

        break;



    case 0xA000:

        I = nnn;

        break;



    case 0xD000:
    {

        V[0xF] = 0;


        for(int row = 0; row < n; row++)
        {
            uint8_t sprite = memory[I + row];


            for(int col = 0; col < 8; col++)
            {
                if(sprite & (0x80 >> col))
                {

                    int pixelX = (V[x] + col) % 64;
                    int pixelY = (V[y] + row) % 32;


                    int index = pixelX + pixelY * 64;


                    if(display[index])
                        V[0xF] = 1;


                    display[index] ^= 1;
                }
            }
        }


        drawFlag = true;

        break;
    }



    case 0xF000:

        switch(nn)
        {

        case 0x07:

            V[x] = delay_timer;

            break;


        case 0x15:

            delay_timer = V[x];

            break;


        case 0x18:

            sound_timer = V[x];

            break;



        case 0x1E:

            I += V[x];

            break;



        case 0x29:

            I = 0x50 + (V[x] * 5);

            break;



        case 0x55:

            for(int i = 0; i <= x; i++)
                memory[I+i] = V[i];

            break;



        case 0x65:

            for(int i = 0; i <= x; i++)
                V[i] = memory[I+i];

            break;

        }

        break;



    default:

        std::cout
        << "Unknown opcode: "
        << std::hex
        << opcode
        << "\n";

        break;

    }

}






void Chip_8::updateTimers()
{

    if(delay_timer > 0)
        delay_timer--;


    if(sound_timer > 0)
    {
        sound_timer--;

        if(sound_timer == 0)
            std::cout << "BEEP\n";
    }

}