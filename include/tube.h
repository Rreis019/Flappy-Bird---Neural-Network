#include "sprite.h"
#include "vec2.h"


#include <SDL2/SDL_image.h>

class Tube
{
public:
    Tube();
    Tube(int x,Sprite* topPipe,Sprite* bodyPipe);
    void onUpdate();
    void onRender();
    vec2 topTubePos;
    vec2 bottomTubePos;
    void getRect(SDL_Rect* top,SDL_Rect* bot);
    int getW();
    int getH();
    bool resetScore = false; //when bird score the resetScore turns true
private:
    Sprite* topPipe;
    Sprite* bodyPipe;
};