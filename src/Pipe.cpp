#include "Pipe.h"

void Pipe::genHeight(int i)
{
    botPipeHeight[i] = Gen(20, screenHEIGHT / 2 + 60);
    topPipeHeight[i] = screenHEIGHT - botPipeHeight[i] - spaceUD - groundHEIGHT;
    if (topPipeHeight[i] <= 20)
    {
        topPipeHeight[i] = 0;
        botPipeHeight[i] -= 20;
    }
}

void Pipe::initPipeHeight(int i)
{
    genHeight(i);
    Xpos[i] = screenWIDTH + i * (screenWIDTH / 2 + pipeWidth / 2) + 100;
    isPassed = 0;
}

void Pipe::Update(int i, bool isTopPipe)
{
    if (Xpos[i] <= -pipeWidth)
    {
        genHeight(i);
        Xpos[i] = screenWIDTH;
        isPassed = 0;
    }
    int Ypos = (isTopPipe ? 0 : screenHEIGHT - botPipeHeight[i] - groundHEIGHT);
    int H = isTopPipe ? topPipeHeight[i] : botPipeHeight[i];
    setDest(Xpos[i], Ypos, pipeWidth, H);
    Xpos[i] -= isTopPipe;
}

int Pipe::getXpos(int i)
{
    return Xpos[i];
}

bool Pipe::GetPassedState()
{
    return isPassed;
}

void Pipe::SetPassedState()
{
    isPassed = 1;
}

int Pipe::Gen(int lo, int hi)
{
    return rng() % (hi - lo + 1) + lo;
}
