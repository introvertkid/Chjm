#pragma once
#include "Object.h"

class Player : public Object
{
private:
    const int screenWIDTH = 480;
    const int screenHEIGHT = 650;
    const int groundYpos = 542;
    int animationFrame = 0;
    int currentSkin = 0;

    double gravity = 0.2;
    double jumpHeight = -6;
    double Ypos = screenHEIGHT / 2;
    double accelerator = 0;
    double currentJumpTimer;
    double lastJumpTimer = 0;
    bool jumpState;

public:
    void Update();
    bool isJumping();
    void Jump();
    void Gravity();
    void setNewPlayer();
    void changeSkin();
};