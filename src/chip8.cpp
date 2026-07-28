#include "chip8.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <chrono>



void Chip_8::initialize()
{
    pc = 0x200;

    I = 0;

    sp = 0;


    delayTimer = 0;

    soundTimer = 0;


    drawFlag = false;


    std::fill(memory.begin(), memory.end(), 0);

    std::fill(V.begin(), V.end(), 0);

    std::fill(stack.begin(), stack.end(), 0);

    std::fill(display.begin(), display.end(), 0);

    std::fill(keypad.begin(), keypad.end(), 0);



    loadFontset();


    std::cout << "CHIP-8 initialized\n";
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

    std::ifstream rom(filename, std::ios::binary);


    if(!rom)
    {
        std::cerr
            << "Failed to open ROM: "
            << filename
            << "\n";

        return false;
    }



    rom.seekg(0, std::ios::end);

    auto size = rom.tellg();

    rom.seekg(0, std::ios::beg);



    if(size > memory.size() - 0x200)
    {
        std::cerr << "ROM too large\n";
        return false;
    }



    rom.read(
        reinterpret_cast<char*>(&memory[0x200]),
        size
    );



    std::cout
        << "Loaded ROM: "
        << filename
        << " ("
        << size
        << " bytes)\n";


    return true;

}





void Chip_8::emulateCycle()
{

    uint16_t opcode =
        (memory[pc] << 8) |
        memory[pc + 1];



    uint8_t x =
        (opcode & 0x0F00) >> 8;


    uint8_t y =
        (opcode & 0x00F0) >> 4;


    uint8_t n =
        opcode & 0x000F;


    uint8_t nn =
        opcode & 0x00FF;


    uint16_t nnn =
        opcode & 0x0FFF;



    pc += 2;



    switch(opcode & 0xF000)
    {


        case 0x0000:

            if(opcode == 0x00E0)
            {
                std::fill(
                    display.begin(),
                    display.end(),
                    0
                );

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




        case 0x5000:

            if(V[x] == V[y])
                pc += 2;

            break;




        case 0x6000:

            V[x] = nn;

            break;




        case 0x7000:

            V[x] += nn;

            break;




        case 0x8000:

            switch(n)
            {

                case 0x0:
                    V[x] = V[y];
                    break;


                case 0x1:
                    V[x] |= V[y];
                    break;


                case 0x2:
                    V[x] &= V[y];
                    break;


                case 0x3:
                    V[x] ^= V[y];
                    break;


                case 0x4:
                {
                    uint16_t result =
                        V[x] + V[y];


                    V[0xF] =
                        result > 255;


                    V[x] =
                        result & 0xFF;

                    break;
                }



                case 0x5:

                    V[0xF] =
                        V[x] > V[y];


                    V[x] -= V[y];

                    break;



                case 0x6:

                    V[0xF] =
                        V[x] & 1;


                    V[x] >>= 1;

                    break;



                case 0x7:

                    V[0xF] =
                        V[y] > V[x];


                    V[x] =
                        V[y] - V[x];

                    break;



                case 0xE:

                    V[0xF] =
                        (V[x] & 0x80) >> 7;


                    V[x] <<= 1;

                    break;

            }

            break;




        case 0x9000:

            if(V[x] != V[y])
                pc += 2;

            break;




        case 0xA000:

            I = nnn;

            break;




        case 0xC000:

            V[x] =
                (rand() % 256) & nn;

            break;




        case 0xD000:
        {

            V[0xF] = 0;


            for(int row = 0; row < n; row++)
            {

                uint8_t sprite =
                    memory[I + row];


                for(int col = 0; col < 8; col++)
                {

                    if(sprite & (0x80 >> col))
                    {

                        int px =
                            (V[x] + col) % 64;


                        int py =
                            (V[y] + row) % 32;



                        int index =
                            px + py * 64;



                        if(display[index])
                            V[0xF] = 1;



                        display[index] ^= 1;

                    }

                }

            }


            drawFlag = true;

            break;

        }




        case 0xE000:

            if((opcode & 0x00FF) == 0x9E)
            {

                if(keypad[V[x]])
                    pc += 2;

            }


            else if((opcode & 0x00FF) == 0xA1)
            {

                if(!keypad[V[x]])
                    pc += 2;

            }


            break;





        case 0xF000:

            switch(nn)
            {


                case 0x07:

                    V[x] = delayTimer;

                    break;



                case 0x15:

                    delayTimer = V[x];

                    break;



                case 0x18:

                    soundTimer = V[x];

                    break;



                case 0x0A:
                {

                    bool pressed = false;


                    for(int i = 0; i < 16; i++)
                    {

                        if(keypad[i])
                        {

                            V[x] = i;

                            pressed = true;

                        }

                    }


                    if(!pressed)
                        pc -= 2;


                    break;

                }



                case 0x29:

                    I = 0x50 + (V[x] * 5);

                    break;



                case 0x33:

                    memory[I] =
                        V[x] / 100;


                    memory[I+1] =
                        (V[x] / 10) % 10;


                    memory[I+2] =
                        V[x] % 10;

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

    }

}






void Chip_8::updateTimers()
{

    static auto last =
        std::chrono::steady_clock::now();



    auto now =
        std::chrono::steady_clock::now();



    if(std::chrono::duration_cast<std::chrono::milliseconds>(now-last).count() >= 16)
    {

        if(delayTimer > 0)
            delayTimer--;


        if(soundTimer > 0)
            soundTimer--;


        last = now;

    }

}