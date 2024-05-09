#pragma once
#include "Object.h"
#include <random>
#include <chrono>

static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
static int topPipeHeight[2];
static int botPipeHeight[2];
static int Xpos[2];

class Pipe : public Object
{
private:
    const int screenWIDTH = 480;
    const int screenHEIGHT = 650;
    const int spaceUD = 200;
    const int pipeWidth = 70;
    int pipeH;
    bool isPassed = 0;

public:
    Pipe();
    void Update(int i, bool isTopPipe);
    void initPipeHeight();
    int Gen(int lo, int hi);
    bool GetPassedState();
    void SetPassedState();
    int GetXpos(int i);
};