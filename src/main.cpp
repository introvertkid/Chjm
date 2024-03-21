#include "Game.h"

Game *myGame = new Game();

int main(int argc, char *argv[])
{
    myGame->Init();

    while (myGame->getGameState())
    {
        myGame->Event();
    }

    myGame->Close();

    return 0;
}