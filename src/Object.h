#pragma once
#include "TextureManager.h"

class Object
{
private:
    SDL_Rect src, dest;
    SDL_Texture *Texture;

public:
    SDL_Texture *getTexture();
    SDL_Rect &getSrc();
    SDL_Rect &getDest();
    void setSrc(int x, int y, int w, int h);
    void setDest(int x, int y, int w, int h);
    void CreateTexture(const char *path, SDL_Renderer *ren);
    void Render(SDL_Renderer *ren);
};