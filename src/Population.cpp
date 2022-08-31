#include "Population.h"
#include "main.h"
#include "utils.h"
#include "constants.h"
#include "window.h"

Population population;

Population::Population(){}
Population::Population(int totalPopulation)
{
    this->birds.resize(totalPopulation);
    this->brains.resize(totalPopulation);
    vec2 start = {WINDOW_WIDTH/4 - allSprites[SFLAPPY_BIRD_PORTUGAL].w*BIRD_SCALE/4,WINDOW_HEIGHT/2 - allSprites[SFLAPPY_BIRD_PORTUGAL].h*BIRD_SCALE/2};

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
        if(birds[i].isDead){
            birds[i].brain->fitness = fit;
            birds.erase(birds.begin() + i);
            i--;
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

#include <algorithm>
void Population::nextGen()
{
    std::sort(this->brains.begin(),this->brains.end(),[](NetBot a,NetBot b){
        return a.fitness > b.fitness;
    });

    //printf("sise[0] -> %d\n",brains[0].neurons.size());
  
    for(int i = 1;i < brains.size();i++){
        brains[i] = NetBot::mutate(brains[0]);
        brains[i].fitness = 0;        
    } 
    
    ///printf("sise[0] -> %d\n",brains[52].neurons.size());
    printf("brain[52] -> %lf -> %lf\n",brains[52].weights[0][0],brains[52].weights[0][0]);
    
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
