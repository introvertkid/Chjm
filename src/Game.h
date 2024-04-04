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
    const int WIDTH = 480;
    const int HEIGHT = 650;
    Player player;
    Background bg;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
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