#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "Player.h"
#include "Background.h"

using namespace std;

class Game
{
private:
    Player player;
    Background bg;
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
    void Render();
    void Update();
};