#include "renderer.hpp"

#include <iostream>


bool Renderer::initialize()
{

    window = SDL_CreateWindow(
        "CHIP-8 Emulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH * SCALE,
        HEIGHT * SCALE,
        SDL_WINDOW_SHOWN
    );


    if(!window)
    {
        std::cerr << "Failed to create SDL window: "
                  << SDL_GetError()
                  << "\n";

        return false;
    }



    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );


    if(!renderer)
    {
        std::cerr << "Failed to create renderer: "
                  << SDL_GetError()
                  << "\n";


        SDL_DestroyWindow(window);

        window = nullptr;

        return false;
    }


    return true;
}





void Renderer::draw(const Chip_8& chip8)
{

    SDL_SetRenderDrawColor(
        renderer,
        0,
        0,
        0,
        255
    );


    SDL_RenderClear(renderer);



    SDL_SetRenderDrawColor(
        renderer,
        255,
        255,
        255,
        255
    );



    for(int y = 0; y < HEIGHT; y++)
    {

        for(int x = 0; x < WIDTH; x++)
        {

            int index = x + (y * WIDTH);



            if(chip8.display[index])
            {

                SDL_Rect pixel;


                pixel.x = x * SCALE;

                pixel.y = y * SCALE;

                pixel.w = SCALE;

                pixel.h = SCALE;



                SDL_RenderFillRect(
                    renderer,
                    &pixel
                );

            }

        }

    }



    SDL_RenderPresent(renderer);

}





void Renderer::shutdown()
{

    if(renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }


    if(window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

}