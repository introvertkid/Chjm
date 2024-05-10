#include "Ground.h"

void Ground::Update()
{
    setDest(Xpos, Ypos, screenWIDTH, screenHEIGHT - Ypos);
    Xpos--;
    if (Xpos < 10)
        Xpos = 0;
}

int Ground::getXpos()
{
    return Xpos;
}