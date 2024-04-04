#include "Game.h"

Game *myGame = new Game();

int main(int argc, char *argv[])
{
    myGame->Init();

    const int FPS = 120;
    const double delayTime = 1000 / 120;
    double lastTime = 0, currentFrameTime = 0;

    while (myGame->getGameState())
    {
        lastTime = SDL_GetTicks();

        myGame->Update();
        myGame->Event();
        myGame->Render();

        currentFrameTime = SDL_GetTicks() - lastTime;
        if (currentFrameTime < delayTime)
        {
            SDL_Delay(delayTime - currentFrameTime);
        }
    }

    myGame->Close();

    return 0;
}