#pragma once
#include "Object.h"

class Prompt : public Object
{
private:
    int animationFrame = 0;

public:
    void Update();
};