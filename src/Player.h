#pragma once
#include "Object.h"

class Player : public Object
{
private:
    double gravity = 0.2;
    const int playerWidth = 19;
    const int playerHeight = 16;
    int animationFrame = 0;

    double jumpHeight = -6;
    double Ypos = 256;
    double accelerator1 = 0, accelerator2 = 0;
    double currentJumpTimer;
    double lastJumpTimer = 0;
    bool jumpState;

    SDL_Texture *Texture1;
    SDL_Texture *Texture2;

public:
    void Render(SDL_Renderer *ren);
    bool isJumping();
    void Jump();
    void Gravity();
    // void CreateTexture1(const char *path, SDL_Renderer *ren);
    // void CreateTexture2(const char *path, SDL_Renderer *ren);
};