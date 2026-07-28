#include "keyboard.hpp"



uint8_t Keyboard::mapKey(SDL_Keycode key)
{

    switch(key)
    {

        case SDLK_1: return 0x1;
        case SDLK_2: return 0x2;
        case SDLK_3: return 0x3;
        case SDLK_4: return 0xC;


        case SDLK_q: return 0x4;
        case SDLK_w: return 0x5;
        case SDLK_e: return 0x6;
        case SDLK_r: return 0xD;


        case SDLK_a: return 0x7;
        case SDLK_s: return 0x8;
        case SDLK_d: return 0x9;
        case SDLK_f: return 0xE;


        case SDLK_z: return 0xA;
        case SDLK_x: return 0x0;
        case SDLK_c: return 0xB;
        case SDLK_v: return 0xF;


        default:
            return 0xFF;

    }

}





void Keyboard::handleInput(Chip_8& chip8, bool& running)
{

    SDL_Event event;



    while(SDL_PollEvent(&event))
    {

        if(event.type == SDL_QUIT)
        {
            running = false;
        }



        if(event.type == SDL_KEYDOWN)
        {

            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                running = false;
            }



            uint8_t key =
                mapKey(event.key.keysym.sym);



            if(key != 0xFF)
            {
                chip8.keypad[key] = 1;
            }

        }





        if(event.type == SDL_KEYUP)
        {

            uint8_t key =
                mapKey(event.key.keysym.sym);



            if(key != 0xFF)
            {
                chip8.keypad[key] = 0;
            }

        }

    }

}