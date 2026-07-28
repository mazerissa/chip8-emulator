#pragma once

#include <SDL2/SDL.h>

#include "chip8.hpp"



class Renderer
{

public:

    bool initialize();

    void draw(const Chip_8& chip8);

    void shutdown();



private:

    SDL_Window* window = nullptr;

    SDL_Renderer* renderer = nullptr;



    static constexpr int WIDTH = 64;

    static constexpr int HEIGHT = 32;

    static constexpr int SCALE = 10;

};