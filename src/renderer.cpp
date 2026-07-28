#include "renderer.hpp"

#include <iostream>


bool Renderer::initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL initialization failed: "
                  << SDL_GetError()
                  << '\n';

        return false;
    }


    window = SDL_CreateWindow(
        "CHIP-8 Emulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        64 * SCALE,
        32 * SCALE,
        SDL_WINDOW_SHOWN
    );


    if (!window)
    {
        std::cerr << "Window creation failed: "
                  << SDL_GetError()
                  << '\n';

        return false;
    }


    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );


    if (!renderer)
    {
        std::cerr << "Renderer creation failed: "
                  << SDL_GetError()
                  << '\n';

        return false;
    }


    std::cout << "Renderer initialized\n";

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


    for (int y = 0; y < 32; y++)
    {
        for (int x = 0; x < 64; x++)
        {
            int index = x + (y * 64);


            if (chip8.display[index])
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
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }


    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }


    SDL_Quit();
}