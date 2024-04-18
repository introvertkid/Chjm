#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "TextureManager.h"
#include "Player.h"
#include "Background.h"
#include "Pipe.h"
#include "TextObject.h"

using namespace std;

class Game
{
private:
    const int screenWIDTH = 480;
    const int screenHEIGHT = 650;
    bool gameState;
    bool isAnyKeyPressed;
    bool updatePipe2;
    bool isDead;

    Player player;
    Background bg;
    Pipe topPipe[2];
    Pipe botPipe[2];

    TTF_Font *scoreFont;
    SDL_Color White = {255, 255, 255};
    SDL_Surface *surfaceMessage;
    SDL_Texture *Message;
    SDL_Rect Message_rect;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

public:
    Game();
    bool getGameState();
    bool detectCollision();
    void Init();
    void Close();
    void Event();
    void Render();
    void Update();
};