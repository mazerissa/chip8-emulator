#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <iostream>

#include "chip8.hpp"
#include "renderer.hpp"
#include "keyboard.hpp"



int main()
{

    std::cout << "CHIP-8 Emulator\n\n";



    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {

        std::cerr
            << "SDL initialization failed: "
            << SDL_GetError()
            << "\n";

        return 1;
    }



    Chip_8 chip8;

    chip8.initialize();


// put the game that you want here 
    if(!chip8.loadROM("roms/games/Breakout [Carmelo Cortez, 1979].ch8"))
    {

        SDL_Quit();

        return 1;
    }





    Renderer renderer;


    if(!renderer.initialize())
    {

        SDL_Quit();

        return 1;
    }





    Keyboard keyboard;



    bool running = true;



    while(running)
    {

        keyboard.handleInput(
            chip8,
            running
        );

        for(int i = 0; i < 10; i++)
        {
            chip8.emulateCycle();
        }



        chip8.updateTimers();



        if(chip8.drawFlag)
        {

            renderer.draw(chip8);

            chip8.drawFlag = false;

        }



        SDL_Delay(16);

    }





    renderer.shutdown();


    SDL_Quit();



    return 0;
}