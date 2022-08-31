#include "sprite.h"
#include <vector>
#include <string>

class SDL_Texture;

class CustomFont{
    public:
        CustomFont(){}
        CustomFont(Sprite* letterTexture,std::string letters, int width, int height);
        void draw(int x, int y,bool centered,char const*format,...);

        int getTextW(char* name) { return (lettersWidth * strlen(name))*scale; }
        int getTextH() { return lettersHeight*scale; }
        void setScale(short s){this->scale = s;}
    private:
        Sprite* lettersImages = NULL;
        std::string allLetters = "";
        short scale = 1;
	    int lettersWidth = 0, lettersHeight = 0;
};