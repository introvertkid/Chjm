#include "Pipe.h"

Pipe::Pipe()
{
    // Xpos = screenWIDTH;
}

void Pipe::initPipeHeight()
{
    for (int i = 0; i < 2; i++)
    {
        botPipeHeight[i] = Gen(10, screenHEIGHT / 2);
        topPipeHeight[i] = screenHEIGHT - botPipeHeight[i] - spaceUD;
        Xpos[i] = screenWIDTH;
    }
}

void Pipe::Update(int i, bool isTopPipe)
{
    if (Xpos[i] <= -pipeWidth)
    {
        botPipeHeight[i] = Gen(10, screenHEIGHT / 2);
        topPipeHeight[i] = screenHEIGHT - botPipeHeight[i] - spaceUD;
        Xpos[i] = screenWIDTH;
        isPassed = 0;
    }
    int Ypos = (isTopPipe ? 0 : screenHEIGHT - botPipeHeight[i]);
    int H = isTopPipe ? topPipeHeight[i] : botPipeHeight[i];
    setDest(Xpos[i], Ypos, pipeWidth, H);
    Xpos[i] -= isTopPipe;
}

int Pipe::GetXpos(int i)
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
