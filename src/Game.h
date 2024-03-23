#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"

using namespace std;

class Game
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *screenSurface;
    SDL_Event windowEvent;
    SDL_Texture *player;
    SDL_Rect srcPLayer, destPlayer;
    bool gameState;

public:
    Game();
    bool getGameState();
    void Init();
    void Close();
    void Event();
    void Render();
    void Update();
};