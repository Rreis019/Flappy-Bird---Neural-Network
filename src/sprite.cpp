#include "sprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Sprite loadSprite(SDL_Renderer* rend,char* filename)
{
    Sprite sprite;
    SDL_Surface * surface = IMG_Load(filename);
    sprite.w = surface->w;
    sprite.h = surface->h;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rend,surface);
    sprite.texture = texture;
    SDL_FreeSurface(surface);
    return sprite;
}