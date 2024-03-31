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
                player.CreateTexture("image/bird0.png", renderer);
                bg.CreateTexture("image/bgDay.png", renderer);
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
    player.setSrc(0, 0, 80, 60);
    player.setDest(0, 0, 40, 60);
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
    bg.Render(renderer, bg.getTexture());
    player.Render(renderer, player.getTexture(), player.getSrc(), player.getDest());
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