#pragma once
#include <vector>
#include "bird.h"
#include "tube.h"

enum SpritesIndex{
    SBACKGROUND = 0,
    SFLOOR = 1,
    SFLAPPY_BIRD_PORTUGAL = 2,
    STUBE_GREEN = 5,
    STUBE_RED = 7,
    SCORE_FONT = 9
};

extern std::vector<Sprite> allSprites;
extern std::vector<Tube> tubes;
extern Bird bird;
extern int score;
void restartGame();