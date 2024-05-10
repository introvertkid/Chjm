#include "Pipe.h"

Pipe::Pipe()
{
    // Xpos = screenWIDTH;
}

void Pipe::initPipeHeight(int i)
{
    botPipeHeight[i] = Gen(10, screenHEIGHT / 2);
    topPipeHeight[i] = screenHEIGHT - botPipeHeight[i] - spaceUD;
    Xpos[i] = screenWIDTH + i * (screenWIDTH / 2 + pipeWidth / 2);
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
