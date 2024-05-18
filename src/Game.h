#pragma once
#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "TextureManager.h"
#include "Player.h"
#include "Background.h"
#include "Pipe.h"
#include "TextObject.h"
#include "Button.h"
#include "Ground.h"
#include "Prompt.h"

using namespace std;

class Game
{
private:
    const int screenWIDTH = 480;
    const int screenHEIGHT = 650;
    const int groundHEIGHT = 108;
    int score;
    bool gameState;
    bool isAnyKeyPressed;
    bool isDead;
    bool isPlaying;
    bool showPrompt;

    Player player;
    Background bg;
    Ground gr1, gr2;
    Pipe topPipe[2];
    Pipe botPipe[2];
    Prompt prompt;
    Object Highscore;

    Button buttons[6];
    enum
    {
        PLAY,
        OPTIONS,
        EXIT,
        REPLAY,
        BACK,
        HOWTOPLAY,
    };

    TTF_Font *scoreFont;
    SDL_Color blackColor = {0, 0, 0};
    TextObject scoreText, HighscoreText;

    Mix_Chunk *wingSound, *hitSound, *pointSound;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

public:
    Game();
    bool getGameState();
    bool detectCollision();
    bool insideButton(Button b);
    void Init();
    void Close();
    void Event();
    void Render();
    void Update();
    void newGame();
};