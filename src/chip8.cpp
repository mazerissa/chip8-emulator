#include "chip8.hpp"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>


void Chip_8::initialize()
{
    pc = 0x200;
    I = 0;
    sp = 0;


    std::fill(memory.begin(), memory.end(), 0);

    std::fill(V.begin(), V.end(), 0);

    std::fill(stack.begin(), stack.end(), 0);

    std::fill(display.begin(), display.end(), 0);
    std::fill(keypad.begin(), keypad.end(), 0);

    std::cout << "CHIP-8 initialized\n";
}



bool Chip_8::loadROM(const std::string& filename)
{
    std::ifstream rom(filename, std::ios::binary);


    if (!rom.is_open())
    {
        std::cerr << "Failed to open ROM: "
                  << filename
                  << '\n';

        return false;
    }


    rom.seekg(0, std::ios::end);

    const std::streamsize size = rom.tellg();

    rom.seekg(0, std::ios::beg);



    if (size <= 0)
    {
        std::cerr << "ROM is empty\n";
        return false;
    }



    constexpr size_t start = 0x200;


    if (static_cast<size_t>(size) > memory.size() - start)
    {
        std::cerr << "ROM too large\n";
        return false;
    }



    rom.read(
        reinterpret_cast<char*>(memory.data() + start),
        size
    );


    std::cout << "Loaded ROM: "
              << filename
              << " ("
              << size
              << " bytes)\n";


    return true;
}



void Chip_8::emulateCycle()
{
    if (pc >= memory.size() - 1)
    {
        std::cerr << "PC out of memory bounds\n";
        return;
    }



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



    std::cout
        << "PC: 0x"
        << std::hex
        << pc
        << " Opcode: 0x"
        << opcode
        << '\n';



    switch(opcode & 0xF000)
    {

        case 0x1000:
        {
            pc = nnn;
            return;
        }

        case 0x2000:
        {
            if (sp >= stack.size())
            {
                std::cerr << "Stack overflow\n";
                return;
            }


            stack[sp] = pc + 2;
            sp++;

            pc = nnn;

            return;
        }

        case 0x0000:
        {
            if ((opcode & 0x00FF) == 0x00EE)
            {
                if (sp == 0)
                {
                    std::cerr << "Stack underflow\n";
                    return;
                }


                sp--;

                pc = stack[sp];

                return;
            }


            break;
        }

        case 0x3000:
        {
            if (V[x] == nn)
                pc += 2;

            break;
        }

        case 0x4000:
        {
            if (V[x] != nn)
                pc += 2;

            break;
        }

        case 0x5000:
        {
            if (V[x] == V[y])
                pc += 2;

            break;
        }

        case 0x6000:
        {
            V[x] = nn;
            break;
        }

        case 0x7000:
        {
            V[x] += nn;
            break;
        }


        case 0x8000:
        {
            switch(opcode & 0x000F)
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

                    V[0xF] = result > 255;

                    V[x] =
                        result & 0xFF;

                    break;
                }



                case 0x5:
                {
                    V[0xF] =
                        V[x] >= V[y];

                    V[x] -= V[y];

                    break;
                }



                case 0x6:
                {
                    V[0xF] =
                        V[x] & 1;

                    V[x] >>= 1;

                    break;
                }



                case 0x7:
                {
                    V[0xF] =
                        V[y] >= V[x];

                    V[x] =
                        V[y] - V[x];

                    break;
                }



                case 0xE:
                {
                    V[0xF] =
                        (V[x] & 0x80) >> 7;

                    V[x] <<= 1;

                    break;
                }

            }

            break;
        }


        case 0xA000:
        {
            I = nnn;
            break;
        }

        case 0xD000:
        {
            V[0xF] = 0;


            for (int row = 0; row < n; row++)
            {
                uint8_t sprite =
                    memory[I + row];


                for (int col = 0; col < 8; col++)
                {
                    if (sprite & (0x80 >> col))
                    {

                        int pixelX =
                            (V[x] + col) % 64;

                        int pixelY =
                            (V[y] + row) % 32;


                        int index =
                            pixelX + pixelY * 64;



                        if(display[index])
                            V[0xF] = 1;



                        display[index] ^= 1;
                    }
                }
            }


            break;
        }

        case 0xE000:
{
    switch(opcode & 0x00FF)
    {

        case 0x9E:
        {
            if(keypad[V[x]])
            {
                pc += 2;
            }

            break;
        }


        case 0xA1:
        {
            if(!keypad[V[x]])
            {
                pc += 2;
            }

            break;
        }

    }

    break;
}

        case 0xF000:
        {
            switch(opcode & 0x00FF)
            {

                case 0x1E:
                {
                    I += V[x];
                    break;
                }

                case 0x55:
                {
                    for(int i = 0; i <= x; i++)
                    {
                        memory[I+i] = V[i];
                    }

                    break;
                }

                case 0x65:
                {
                    for(int i = 0; i <= x; i++)
                    {
                        V[i] = memory[I+i];
                    }

                    break;
                }



                default:
                    std::cout
                        << "Unknown FX opcode\n";
                    break;
            }


            break;
        }



        default:
        {
            std::cout
                << "Unknown opcode: 0x"
                << std::hex
                << opcode
                << '\n';

            return;
        }

    }



    pc += 2;
}