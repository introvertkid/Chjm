#include "Game.h"

Game::Game()
{
    window = NULL;
    renderer = NULL;
    gameState = 0;

    player.setSrc(0, 0, 19, 16);
    player.setDest(0, 0, 50, 50);
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
                                  WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
        if (window == NULL)
        {
            cout << "Window could not be created " << SDL_GetError() << '\n';
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (renderer)
            {
                cout << "Succeeded !" << '\n';
                gameState = 1;
                player.CreateTexture("image/2birds.png", renderer);
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
}

void Game::Event()
{
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
    {
        gameState = 0;
        return;
    }
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_SPACE)
        {
            if (!player.isJumping())
                player.Jump();
            else
                player.Gravity();
        }
    }
    else
        player.Gravity();
}

void Game::Render()
{
    SDL_RenderClear(renderer);

    bg.Render(renderer);
    player.Render(renderer);

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