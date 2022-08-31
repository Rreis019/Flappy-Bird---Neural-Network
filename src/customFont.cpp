#include "customFont.h"
#include <SDL2/SDL.h>
#include "window.h"
CustomFont::CustomFont(Sprite* lettersTexture,std::string letters, int width, int height)
{
    allLetters = letters;
	this->lettersImages = lettersTexture;
    lettersWidth = width;
	lettersHeight = height;
}

void CustomFont::draw(int x, int y,bool centered,char const*format,...)
{
    va_list arglist;
    va_start(arglist, format);

    char *buffer = (char*)malloc(255); 
    vsnprintf(buffer, 255, format, arglist);
    va_end(arglist);
    free(buffer);

    if(centered){
        x-= getTextW(buffer)/2;
    }

    for (int i = 0; i < strlen(buffer); i++)
	{
        auto index = allLetters.find(buffer[i]);

		if (index == std::string::npos)
			continue;

        SDL_Rect rect = {x+ i * lettersWidth*scale,y, lettersWidth*scale ,lettersHeight*scale};
        Sprite* Sletter = lettersImages + index;
        SDL_RenderCopy(renderer,Sletter->texture,NULL,&rect);
	}
}
