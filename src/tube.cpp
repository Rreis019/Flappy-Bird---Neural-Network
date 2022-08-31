#include "tube.h"
#include "window.h"
#include "utils.h"

Tube::Tube(){}

#define TUBE_GAP 72*BIRD_SCALE
#define TOP_SIZE_PART 13*BIRD_SCALE

#define TUBE_VELOCITY 200

Tube::Tube(int x,Sprite* topPipe,Sprite* bodyPipe)
{
    this->topPipe = topPipe;
    this->bodyPipe = bodyPipe;

    this->bottomTubePos.x = (float)x;
    this->topTubePos.x = (float)x;


    this->bottomTubePos.y = RAND_INT(TUBE_GAP,WINDOW_HEIGHT-TOP_SIZE_PART);
    this->topTubePos.y = (bottomTubePos.y-TUBE_GAP)-topPipe->h*BIRD_SCALE+TOP_SIZE_PART;
    this->resetScore = false;
}

void Tube::onUpdate()
{
    if( (topTubePos.x+bodyPipe->w*BIRD_SCALE)  < 0 )
    {
        topTubePos.x = WINDOW_HEIGHT + (bodyPipe->w+33*BIRD_SCALE)*BIRD_SCALE;
        bottomTubePos.x = WINDOW_HEIGHT + (bodyPipe->w+33*BIRD_SCALE)*BIRD_SCALE;

        this->bottomTubePos.y = RAND_INT(TUBE_GAP,WINDOW_HEIGHT-TOP_SIZE_PART);
        this->topTubePos.y = (bottomTubePos.y-TUBE_GAP)-topPipe->h*BIRD_SCALE+TOP_SIZE_PART;
        this->resetScore = false;
    }

    topTubePos.x -= TUBE_VELOCITY *deltaTime;
    bottomTubePos.x -= TUBE_VELOCITY *deltaTime;
}

void Tube::onRender()
{
    SDL_Rect rect1 = {(int)this->topTubePos.x,(int)this->topTubePos.y,topPipe->w*BIRD_SCALE,topPipe->h*BIRD_SCALE};
    SDL_RenderCopy(renderer,topPipe->texture,NULL,&rect1);

    SDL_Rect rect2 = {(int)this->bottomTubePos.x,(int)this->bottomTubePos.y,bodyPipe->w*BIRD_SCALE,bodyPipe->h*BIRD_SCALE};
    SDL_RenderCopy(renderer,bodyPipe->texture,NULL,&rect2);

}


void Tube::getRect(SDL_Rect* top,SDL_Rect* bot)
{
    top->x =(int)this->topTubePos.x; top->y =(int)this->topTubePos.y;
    top->w = this->getW();
    top->h = topPipe->h*BIRD_SCALE;

    bot->x =(int)this->bottomTubePos.x; bot->y =(int)this->bottomTubePos.y;
    bot->w = this->getW();
    bot->h = bodyPipe->h*BIRD_SCALE;
}

int Tube::getW(){
    return topPipe->w*BIRD_SCALE;
}

int Tube::getH(){
    return topPipe->h*BIRD_SCALE;
 }