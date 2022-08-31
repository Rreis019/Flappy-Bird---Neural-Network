#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>

//optional imports
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "sprite.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern bool appIsRunning;
extern float deltaTime;
extern int startTick;

#define ANIMATION(startSpriteIndex,numberSprites,delay) (SDL_GetTicks() / delay ) % numberSprites + startSpriteIndex

void windowCreate(int w,int h,char* titleName);
void windowLoop();
void windowRender();
void windowEvents(SDL_Event* event);
void windowOnStart();

//Input System
bool isKeyDown(int key);
bool isKeyPressed(int key);