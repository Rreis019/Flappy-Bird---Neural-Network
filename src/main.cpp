#include "main.h"
#include "window.h"
#include <ctime>
#include "utils.h"
#include "customFont.h"
#include "Population.h"
#include <string>

std::vector<Sprite> allSprites;
std::vector<Tube> tubes;
CustomFont scoreFont;
float xBackground = 0;

TTF_Font* font;
SDL_Texture* birdsAliveTxt;
SDL_Texture* genTxt;
int textW,textH,genTxtW,genTxtH;
int oldGeneration = 0,oldBirdAliveNum = 0;
int score = 0;


void windowOnStart()
{
    RAND_INT(0,WINDOW_HEIGHT);
    char imagePath[64];
    
    allSprites.push_back(loadSprite(renderer,"assets\\background.png"));
    allSprites.push_back(loadSprite(renderer,"assets\\bfloor.png"));

    #define ASSETS_PATH "assets\\"
    #define LOAD_SPRITES(name,number) \
    for(int i = 0;i < number;i++) { \
    sprintf(imagePath,ASSETS_PATH name "%d.png",i); \
    allSprites.push_back(loadSprite(renderer,imagePath)); } \

    LOAD_SPRITES("fBirdPortugal",3);
    LOAD_SPRITES("tube",4);
    LOAD_SPRITES("scoreFont",10);

    vec2 start = {WINDOW_WIDTH/4 - allSprites[SFLAPPY_BIRD_PORTUGAL].w*BIRD_SCALE/4,WINDOW_HEIGHT/2 - allSprites[SFLAPPY_BIRD_PORTUGAL].h*BIRD_SCALE/2};
    font = TTF_OpenFont("assets\\Comfortaa-Regular.ttf",24);
    assert(font != nullptr);

    SDL_Surface* s = TTF_RenderText_Solid(font,"Generation:0",{0,0,0});
    birdsAliveTxt = SDL_CreateTextureFromSurface(renderer,s);
    genTxtW = s->w;
    genTxtH = s->h;
    SDL_FreeSurface(s);

    SDL_Surface* s2 = TTF_RenderText_Solid(font,"Birds Alive:0",{0,0,0});
    birdsAliveTxt = SDL_CreateTextureFromSurface(renderer,s2);
    textW = s2->w;
    textH = s2->h;
    SDL_FreeSurface(s2);



    tubes.push_back(Tube(WINDOW_WIDTH*1.5,&allSprites[STUBE_GREEN+1],&allSprites[STUBE_GREEN]));
    tubes.push_back(Tube(WINDOW_WIDTH*2,&allSprites[STUBE_RED+1],&allSprites[STUBE_RED]));
    scoreFont = CustomFont(&allSprites[SCORE_FONT],"0123456789",12,18);
    scoreFont.setScale(3);
    population = Population(100);
}

void restartGame()
{
    tubes.clear();
    //vec2 start = {WINDOW_WIDTH/4 - allSprites[SFLAPPY_BIRD_PORTUGAL].w*BIRD_SCALE/4,WINDOW_HEIGHT/2 - allSprites[SFLAPPY_BIRD_PORTUGAL].h*BIRD_SCALE/2};
    //bird.position = start;
    //bird.velocityY = 0;
    tubes.push_back(Tube(WINDOW_WIDTH*0.9,&allSprites[STUBE_GREEN+1],&allSprites[STUBE_GREEN]));
    tubes.push_back(Tube(WINDOW_WIDTH*1.5,&allSprites[STUBE_RED+1],&allSprites[STUBE_RED]));
    score = 0;
    xBackground = 0;
}

void windowEvents(SDL_Event* event)
{
    switch(event->type)
    {               
        case SDL_QUIT:
            appIsRunning = false;
        break;
    }
}

void drawScrollBackground(float& xPos,Sprite* s,float speed)
{
    xPos -= speed * deltaTime;
    xPos = (int)xPos % WINDOW_WIDTH;
    SDL_Rect r = {xPos,0,s->w*3,s->h*3};
    SDL_Rect r2 = {xPos+s->w*3,0,s->w*3,s->h*3};
    SDL_RenderCopy(renderer,s->texture,NULL,&r);
    SDL_RenderCopy(renderer,s->texture,NULL,&r2);
}

void windowRender()
{
    drawScrollBackground(xBackground,&allSprites[SBACKGROUND],100);
    for(int i = 0; i < tubes.size();i++){
        tubes[i].onUpdate();
        tubes[i].onRender();
    }

    if(isKeyPressed(SDL_SCANCODE_INSERT)){restartGame();}
    population.onUpdate();
    scoreFont.draw(WINDOW_WIDTH/2,5,true,"%d",score);

    if(oldGeneration != population.currentGeneration)
    {
        std::string str = "Generation:" + std::to_string(population.currentGeneration);
        //printf("str %s",str.c_str());
        SDL_Surface* s = TTF_RenderText_Solid(font,(const char*)str.c_str(),{0,0,0});
        genTxt = SDL_CreateTextureFromSurface(renderer,s);
        textW = s->w;
        textH = s->h;
        SDL_FreeSurface(s);
        oldGeneration = population.currentGeneration;
    }

    if(oldBirdAliveNum != population.birds.size()){
        std::string str = "Birds Alive:" + std::to_string(population.birds.size());
        SDL_Surface* s2 = TTF_RenderText_Solid(font,str.c_str(),{0,0,0});
        birdsAliveTxt = SDL_CreateTextureFromSurface(renderer,s2);
        genTxtW = s2->w;
        genTxtH = s2->h;
        SDL_FreeSurface(s2);
        oldBirdAliveNum = population.birds.size();
    }

    SDL_Rect r = {0,0,genTxtW,genTxtH};
    SDL_RenderCopy(renderer,genTxt,NULL,&r);

    SDL_Rect r2 = {0,genTxtH,textW,textH};
    SDL_RenderCopy(renderer,birdsAliveTxt,NULL,&r2);

}


int main(int argc, char* argv[])
{
    srand(time(0));
    windowCreate(WINDOW_WIDTH,WINDOW_HEIGHT,(char*)WINDOW_TITLE);
    windowLoop();

    TTF_CloseFont(font);
    SDL_Quit();
    return 0;
}
