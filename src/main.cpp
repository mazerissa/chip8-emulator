#include "chip8.hpp"
#include "renderer.hpp"

#include <iostream>


int main()
{
    Chip_8 chip8;

    chip8.initialize();


    if(!chip8.loadROM("roms/test.ch8"))
    {
        return 1;
    }



    Renderer renderer;


    if(!renderer.initialize())
    {
        return 1;
    }



    bool running = true;


    while(running)
    {

        SDL_Event event;


        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
            }
        }



        chip8.emulateCycle();


        renderer.draw(chip8);


        SDL_Delay(16);
    }



    renderer.shutdown();


    return 0;
}