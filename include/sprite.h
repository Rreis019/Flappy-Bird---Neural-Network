#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


//free Texture when it is not necessary
struct Sprite {
    SDL_Texture* texture;
    int w = 0,h = 0;
};


Sprite loadSprite(SDL_Renderer* rend,char* filename);