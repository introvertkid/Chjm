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
            // screenSurface = SDL_GetWindowSurface(window);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (renderer)
            {
                cout << "Succeeded !" << '\n';
                gameState = 1;
                player = TextureManager::Texture("image/bird0.png", renderer);
                if (player == NULL)
                    cout << "Could not load image";
            }
            else
            {
                cout << "Renderer = NULL !!! " << SDL_GetError() << '\n';
            }
        }
    }
}

void Game::Update()
{
    srcPLayer.h = 60;
    srcPLayer.w = 80;
    srcPLayer.x = srcPLayer.y = 0;

    destPlayer.h = 60;
    destPlayer.w = 40;
    destPlayer.x = destPlayer.y = 0;
}

void Game::Event()
{
    SDL_PollEvent(&windowEvent);
    if (windowEvent.type == SDL_QUIT)
        gameState = 0;
}

void Game::Render()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, player, &srcPLayer, &destPlayer);
    SDL_RenderPresent(renderer);
}

void Game::Close()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    window = NULL;
    renderer = NULL;

    SDL_Quit();
}

bool Game::getGameState()
{
    return gameState;
}