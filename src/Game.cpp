#include "Game.h"

Game::Game()
{
    window = NULL;
    renderer = NULL;
    gameState = isAnyKeyPressed = updatePipe2 = 0;

    player.setSrc(0, 0, 19, 16);
    player.setDest(screenWIDTH / 2, screenHEIGHT / 2, 50, 50);

    for (int i = 0; i < 2; i++)
    {
        topPipe[i].setSrc(0, 0, 25, 100);
        botPipe[i].setSrc(0, 0, 25, 100);
    }
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
                                  screenWIDTH, screenHEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
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
                for (int i = 0; i < 2; i++)
                {
                    topPipe[i].CreateTexture("image/topPipe.png", renderer);
                    botPipe[i].CreateTexture("image/botPipe.png", renderer);
                }
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
    player.Update();

    botPipe[0].botPipeUpdate();
    topPipe[0].topPipeUpdate();
    if (updatePipe2 == 0 && botPipe[0].getXpos() <= screenWIDTH / 2)
        updatePipe2 = 1;
    if (updatePipe2)
    {
        botPipe[1].botPipeUpdate();
        topPipe[1].topPipeUpdate();
    }
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
        isAnyKeyPressed = 1;
        if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_SPACE)
        {
            if (!player.isJumping())
                player.Jump();
            else
                player.Gravity();
        }
    }
    else if (isAnyKeyPressed)
        player.Gravity();
}

void Game::Render()
{
    SDL_RenderClear(renderer);

    bg.Render(renderer);
    player.Render(renderer);
    for (int i = 0; i < 2; i++)
    {
        botPipe[i].Render(renderer);
        topPipe[i].Render(renderer);
    }

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