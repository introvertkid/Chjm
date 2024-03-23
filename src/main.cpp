#include "Game.h"

Game *myGame = new Game();

int main(int argc, char *argv[])
{
    myGame->Init();

    while (myGame->getGameState())
    {
        myGame->Render();
        myGame->Event();
        myGame->Update();
    }

    myGame->Close();

    return 0;
}