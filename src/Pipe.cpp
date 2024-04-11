#include "Pipe.h"

Pipe::Pipe()
{
    Xpos = screenWIDTH;
}

void Pipe::initPipeHeight()
{
    for (int i = 0; i < 2; i++)
    {
        botPipeHeight[i] = Gen(10, screenHEIGHT / 2);
        topPipeHeight[i] = screenHEIGHT - botPipeHeight[i] - spaceUD;
    }
}

void Pipe::Update(int i, bool isTopPipe)
{
    if (Xpos <= -pipeWidth)
    {
        botPipeHeight[i] = Gen(10, screenHEIGHT / 2);
        topPipeHeight[i] = screenHEIGHT - botPipeHeight[i] - spaceUD;
        Xpos = screenWIDTH;
    }
    int Ypos = (isTopPipe ? 0 : screenHEIGHT - botPipeHeight[i]);
    int H = isTopPipe ? topPipeHeight[i] : botPipeHeight[i];
    setDest(Xpos, Ypos, pipeWidth, H);
    Xpos--;
}

int Pipe::getXpos()
{
    return Xpos;
}

int Pipe::Gen(int lo, int hi)
{
    return rng() % (hi - lo + 1) + lo;
}

void Pipe::Render(SDL_Renderer *ren)
{
    SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}
