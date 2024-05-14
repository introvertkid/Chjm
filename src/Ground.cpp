#include "Ground.h"

void Ground::Update(bool isPlaying)
{
    Xpos -= isPlaying;
    if (Xpos <= -480)
        Xpos = 480;
    setDest(Xpos, Ypos, screenWIDTH, screenHEIGHT - Ypos);
}

void Ground::setXpos(int x)
{
    Xpos = x;
}