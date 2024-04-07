#pragma once
#include "Object.h"
#include <random>
#include <chrono>

static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

class Pipe : public Object
{
private:
    const int screenWIDTH = 480;
    const int screenHEIGHT = 650;
    const int spaceRL = 200;
    const int spaceUD = 150;
    const int pipeWidth = 70;
    int Xpos;
    int botPipeHeight;

public:
    Pipe();
    void Render(SDL_Renderer *ren);
    void topPipeUpdate();
    void botPipeUpdate();
    void Update(bool isTopPipe);
    int getXpos();
    int Gen(int lo, int hi);
};