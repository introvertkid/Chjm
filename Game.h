#pragma once
#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

class Game
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *screenSurface;
    SDL_Event windowEvent;
    bool gameState;

public:
    Game();
    bool getGameState();
    void Init();
    void Close();
    void Event();
};