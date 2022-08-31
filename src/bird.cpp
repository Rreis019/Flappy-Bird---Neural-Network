#include "bird.h"
#include "window.h"
#include <math.h>
#include "main.h"

#include "utils.h"

Bird::Bird(){this->velocityY =0;}
Bird::Bird(vec2 startPos,Sprite* sprite)
{
    this->position = {startPos.x,startPos.y};
    this->startSprite = sprite;
    this->currentSprite = sprite;
    this->velocityY = 0;
}

void Bird::jump()
{
    this->velocityY = -BIRD_LIFT;
}

void Bird::onUpdate()
{
    this->velocityY += pow(WORLD_GRAVITY,2) * deltaTime;
    this->position.y += this->velocityY;
    /*
    if(isKeyPressed(SDL_SCANCODE_SPACE)){
        this->jump();
    }
    */
    std::vector<double> data;
    float distanceBottom = 0,distanceTop = 0;
    float minDistanceX = 9999;

    vec2 topClosest,botClosest;
    for(int i = 0; i < tubes.size();i++){
        float deltaX = tubes[i].topTubePos.x - this->position.x;
        
        if(this->position.x >  tubes[i].topTubePos.x + tubes[i].getW()) {continue;}

        if(deltaX < minDistanceX){
            distanceTop = this->position.y - tubes[i].topTubePos.y;
            distanceBottom = this->position.y - tubes[i].bottomTubePos.y;
            minDistanceX = deltaX;
            topClosest = tubes[i].topTubePos;topClosest.y += tubes[i].getH();
            botClosest = tubes[i].bottomTubePos;

        }
    }
    data.push_back(NORMALIZE_VALUE(this->position.y,0,WINDOW_HEIGHT));
    data.push_back(NORMALIZE_VALUE(distanceTop,0,WINDOW_HEIGHT));
    data.push_back(NORMALIZE_VALUE(distanceBottom,0,WINDOW_HEIGHT));
    brain->feedForward(data);

    if(brain->neurons.back()[0] > 0.5f){
        this->jump();
    }

    SDL_RenderDrawLine(renderer,this->position.x + getW()/2,this->position.y + getH()/2 ,topClosest.x,topClosest.y);
    SDL_RenderDrawLine(renderer,this->position.x + getW()/2,this->position.y + getH()/2,botClosest.x,botClosest.y);
    //Colide System
    bool colide = false;
    SDL_Rect rect,topTube,botTube,output;
    rect = getRect();
    for(int i = 0;i < tubes.size();i++){
        tubes[i].getRect(&topTube,&botTube);
        if(SDL_IntersectRect(&rect,&topTube,&output)){colide = true;break;}    
        if(SDL_IntersectRect(&rect,&botTube,&output)){colide = true;break;} 
        if(this->position.x > topTube.x + topTube.w && tubes[i].resetScore == false){
            tubes[i].resetScore = true;
            score++;
        } 
    }

    if(colide){
        this->isDead = true;
    }
    if(this->position.y > WINDOW_HEIGHT || this->position.y + this->currentSprite->h < 0){
        this->isDead = true;
    }

}

SDL_Point center= SDL_Point();

void Bird::onRender()
{
    this->currentSprite = this->startSprite + ANIMATION(0,3,125);
    SDL_Rect rect = getRect();
    float normalizedY = this->velocityY / 10;
    float angle = normalizedY * 45;
    //clamp Angles
    if(angle > 25){angle = 25;}
    else if(angle < -45){angle = -45;}
    SDL_RenderCopyEx(renderer,currentSprite->texture,NULL,&rect,angle,&center,SDL_RendererFlip::SDL_FLIP_NONE);
}
SDL_Rect Bird::getRect(){return {(int)this->position.x,(int)this->position.y,currentSprite->w*BIRD_SCALE,currentSprite->h*BIRD_SCALE};}


int Bird::getW(){
    return (int)this->position.y,currentSprite->w*BIRD_SCALE;
}
int Bird::getH(){
    return currentSprite->h*BIRD_SCALE;
}