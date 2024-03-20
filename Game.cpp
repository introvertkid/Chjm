#include "Game.h"

Game::Game()
{
    window = NULL;
    screenSurface = NULL;
    renderer = NULL;

    gameState = 0;
}

void Game::Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout << "SDL could not be initialized " << SDL_GetError() << '\n';
    }
    else
    {
        window = SDL_CreateWindow("Chjm", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  480, 650, SDL_WINDOW_ALLOW_HIGHDPI);
        if (window == NULL)
        {
            cout << "Window could not be created " << SDL_GetError() << '\n';
        }
        else
        {
            screenSurface = SDL_GetWindowSurface(window);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            gameState = 1;
        }
    }
}

void Game::Close()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    window = NULL;
    renderer = NULL;

    SDL_Quit();
}

void Game::Event()
{
    SDL_PollEvent(&windowEvent);
    if (windowEvent.type == SDL_QUIT)
        gameState = 0;
}

bool Game::getGameState()
{
    return gameState;
}