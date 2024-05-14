#include "Prompt.h"

void Prompt::Update()
{
    animationFrame++;
    animationFrame %= 100;
    setSrc(0, animationFrame / 50 * 102, 507, 102);
}