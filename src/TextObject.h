#pragma once
#include <SDL_ttf.h>
#include "Object.h"

class TextObject : public Object
{
private:
    SDL_Texture *Texture;

public:
    SDL_Texture *getTexture();
    void Render(SDL_Renderer *ren);
    void CreateText(SDL_Renderer *ren, TTF_Font *curFont, SDL_Color color);
};