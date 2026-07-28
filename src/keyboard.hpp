#pragma once

#include <SDL2/SDL.h>
#include "chip8.hpp"

class Keyboard
{
public:

    void handleInput(Chip_8& chip8, bool& running);

};