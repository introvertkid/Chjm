#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "Player.h"
#include "Background.h"
#include "Pipe.h"
#include "TextObject.h"
#include "Button.h"

using namespace std;

class Game
{
private:
    const int screenWIDTH = 480;
    const int screenHEIGHT = 650;
    int score;
    bool gameState;
    bool isAnyKeyPressed;
    bool updatePipe2;
    bool isDead;

    Player player;
    Background bg;
    Pipe topPipe[2];
    Pipe botPipe[2];

    Button PLAY;

    TTF_Font *scoreFont;
    SDL_Color blackColor = {0, 0, 0};
    TextObject scoreText;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

public:
    bool isPlaying = 0;

    Game();
    bool getGameState();
    bool detectCollision();
    bool insideButton(Button b);
    void Init();
    void Close();
    void Event();
    void Render();
    void Update();
};