#pragma once
#include "Object.h"

class Ground : public Object
{
private:
    const int screenWIDTH = 480;
    const int screenHEIGHT = 650;
    const int Ypos = 542;
    int Xpos;

public:
    void Update();
    int getXpos();
};