#include <chrono>
#include <stdio.h>

#include "window.h"

int startTick = 0,EndTick = 0;
float deltaTime = 0;
using namespace std::chrono;
typedef high_resolution_clock Clock;
Clock::time_point lastTime;
void limitFps(int LimitFps)
{
	Clock::time_point time = Clock::now();
	deltaTime = duration_cast<nanoseconds>(time - lastTime).count()  / 1000000000.0f;
	lastTime = time;
	if(deltaTime > (1.0f / LimitFps) * 1.5 ){deltaTime = 1.0f / LimitFps;}

	Uint32 EndTick = SDL_GetTicks();
	int tempDt = EndTick - startTick;
	if ((1000 / LimitFps) > tempDt) {
		SDL_Delay(1000 / LimitFps - (tempDt));
	}
	startTick = SDL_GetTicks();
}


SDL_Window* window;
SDL_Renderer* renderer;
bool appIsRunning;

void windowCreate(int w,int h,char* titleName)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    if(SDL_CreateWindowAndRenderer(w,h,0,&window,&renderer) == -1){
        printf("SDL_CreateWindowAndRenderer failed: %s\n", SDL_GetError());
    }
    
    if(TTF_Init() == -1){
        printf("TTF failed: %s\n", SDL_GetError());
    }
    
    SDL_SetWindowTitle(window,titleName);
    appIsRunning = true;

    
}


#define MAX_KEYS 256
bool keysDown[MAX_KEYS];
bool keysPressed[MAX_KEYS];

bool isKeyDown(int key)
{
    assert(key < MAX_KEYS);
    return keysDown[key];
}

bool isKeyPressed(int key)
{
    assert(key < MAX_KEYS);
    return keysPressed[key];
}

void events()
{
    SDL_Event event;
    memset(keysPressed, 0, sizeof(keysPressed)); 
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {	
		case SDL_KEYDOWN:
    	 	if(event.key.keysym.scancode < MAX_KEYS)
    	 	{
				keysDown[event.key.keysym.scancode] = true;
    	 	}

            break;
		case SDL_KEYUP:
    	 	if(event.key.keysym.scancode < MAX_KEYS)
    	 	{
				keysDown[event.key.keysym.scancode] = false;
				keysPressed[event.key.keysym.scancode] = true;
         
    	 	}
        }
        windowEvents(&event);
    }
}

void windowLoop()
{
    windowOnStart();
    while (appIsRunning)
    {
        limitFps(60);
        events();
        SDL_SetRenderDrawColor(renderer,WINDOW_BACKGROUND);
        SDL_RenderClear(renderer); 
        windowRender();
        SDL_RenderPresent(renderer);
    }
}
