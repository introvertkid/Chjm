#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class TextureManager
{
public:
    static SDL_Texture *Texture(const char *FileLocation, SDL_Renderer *ren);
};