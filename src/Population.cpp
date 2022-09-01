#include "Population.h"
#include "main.h"
#include "utils.h"
#include "constants.h"
#include "window.h"
#include <algorithm>

Population population;

Population::Population(){}
Population::Population(int totalPopulation)
{
    this->birds.resize(totalPopulation);
    this->brains.resize(totalPopulation);
    vec2 start = {WINDOW_WIDTH/4 - allSprites[SFLAPPY_BIRD_PORTUGAL].w*BIRD_SCALE/4,WINDOW_HEIGHT/2 - allSprites[SFLAPPY_BIRD_PORTUGAL].h*BIRD_SCALE/2};


    NetBot loadedModel = NetBot({3,4,1});
    if(loadedModel.load("model.txt")){
        printf("Sucessfly loaded model\n");
        for(int i = 0 ; i < totalPopulation;i++)
        {
            brains[i] = loadedModel;
            start.y = RAND_FLOAT(WINDOW_HEIGHT/4,WINDOW_HEIGHT/2);
            Bird bird = Bird(start,&allSprites[SFLAPPY_BIRD_PORTUGAL]);
            bird.brain = &brains[i];
            this->birds[i] = bird;
        }
        startTick = SDL_GetTicks();
        this->currentGeneration++;
        return;
    }
 
    for(int i = 0 ; i < totalPopulation;i++)
    {
        brains[i] = NetBot({3,4,1});
        start.y = RAND_FLOAT(WINDOW_HEIGHT/4,WINDOW_HEIGHT/2);
        Bird bird = Bird(start,&allSprites[SFLAPPY_BIRD_PORTUGAL]);
        bird.brain = &this->brains[i];
        this->birds[i] = bird;
    }


    startTick = SDL_GetTicks();
    this->currentGeneration++;

}

void Population::onUpdate()
{
    int fit = SDL_GetTicks() - this->startTick;
    for(int i = 0;i < birds.size();i++){
        birds[i].brain->fitness = fit;
        if(birds[i].isDead){
            birds.erase(birds.begin() + i);
            i--;
        }
    }


    if(isKeyPressed(SDL_SCANCODE_S)){
        printf("save");
       for(int i = 0;i < birds.size();i++){
            if(birds[i].isDead == false){
                birds[i].brain->save("model.txt");
                break;
            }
        }
    }


    for(int i = 0;i < birds.size();i++){
        birds[i].onUpdate();
        birds[i].onRender();
    }


    if(birds.size() == 0)
    {
        nextGen();
    }
}

void Population::nextGen()
{
    std::sort(this->brains.begin(),this->brains.end(),[](NetBot a,NetBot b){
        return a.fitness > b.fitness;
    });

    brains[0].save("model.txt");
  
    for(int i = 1;i < brains.size();i++){
        brains[i] = NetBot::mutate(brains[0]);
        brains[i].fitness = 0;        
    } 

    vec2 start = {WINDOW_WIDTH/4 - allSprites[SFLAPPY_BIRD_PORTUGAL].w*BIRD_SCALE/4,WINDOW_HEIGHT/2 - allSprites[SFLAPPY_BIRD_PORTUGAL].h*BIRD_SCALE/2};

    this->birds.clear();
    for(int i = 0 ; i < totalPopulation;i++)
    {
        start.y = RAND_FLOAT(WINDOW_HEIGHT/4,WINDOW_HEIGHT/2);
        Bird bird = Bird(start,&allSprites[SFLAPPY_BIRD_PORTUGAL]);
        bird.brain = &this->brains[i];
        this->birds.push_back(bird);
    }

    restartGame();
    this->startTick = SDL_GetTicks();
    this->currentGeneration++;
}
