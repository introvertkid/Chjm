#include "Pipe.h"

Pipe::Pipe()
{
    botPipeHeight = Gen(10, screenHEIGHT / 2);
    Xpos = screenWIDTH;
}

void Pipe::Update(bool isTopPipe)
{
    if (Xpos <= -pipeWidth)
    {
        botPipeHeight = Gen(10, screenHEIGHT / 2);
        Xpos = screenWIDTH;
    }
    int Ypos = isTopPipe ? 0 : screenHEIGHT - botPipeHeight;
    setDest(Xpos, Ypos, pipeWidth, botPipeHeight);
    Xpos--;
}

void Pipe::topPipeUpdate()
{
    Update(1);
}

void Pipe::botPipeUpdate()
{
    Update(0);
}

int Pipe::getXpos()
{
    return Xpos;
}

// void Pipe::topPipeUpdate()
// {
//     if (Xpos <= pipeWidth)
//     {
//         // botPipeHeight = Gen(10, screenHEIGHT / 2);
//         Xpos = screenWIDTH;
//     }
//     setDest(Xpos, 0, pipeWidth, screenHEIGHT - botPipeHeight - spaceUD);
//     Xpos--;
// }

// void Pipe::botPipeUpdate()
// {
//     if (Xpos <= pipeWidth)
//     {
//         botPipeHeight = Gen(10, screenHEIGHT / 2);
//         Xpos = screenWIDTH;
//     }
//     setDest(Xpos, screenHEIGHT - botPipeHeight, pipeWidth, botPipeHeight);
//     Xpos--;
// }

void Pipe::Render(SDL_Renderer *ren)
{
    SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}

int Pipe::Gen(int lo, int hi)
{
    return rng() % (hi - lo + 1) + lo;
}