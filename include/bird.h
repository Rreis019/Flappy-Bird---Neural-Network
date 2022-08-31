#pragma once
#include "sprite.h"
#include "vec2.h"
#include "neuralNetwork.h"
#include <SDL2/SDL_image.h>

class Bird
{
public:
    Bird();
    Bird(vec2 startPos,Sprite* texture);
    void onUpdate();
    void onRender();
    SDL_Rect getRect();
    vec2 position;
    float velocityY;
    NetBot* brain = NULL;
    bool isDead = false;
    int getW();
    int getH();
private:
    void jump();
    Sprite* startSprite;
    Sprite* currentSprite;

};