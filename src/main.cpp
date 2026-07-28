#include "chip8.hpp"
#include "renderer.hpp"
#include "keyboard.hpp"
#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "CHIP-8 Emulator\n\n";


    Chip_8 chip8;

    chip8.initialize();


    if (!chip8.loadROM("roms/drawtest.ch8"))
{
    return 1;
}


    Renderer renderer;

    if (!renderer.initialize())
    {
        return 1;
    }


    Keyboard keyboard;


    bool running = true;


    while (running)
    {
        keyboard.handleInput(chip8, running);


        chip8.emulateCycle();


        renderer.draw(chip8);


        SDL_Delay(16);
    }


    renderer.shutdown();


    return 0;
}