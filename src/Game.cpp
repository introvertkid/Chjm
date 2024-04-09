#include "Game.h"

Game::Game()
{
    window = NULL;
    renderer = NULL;
    gameState = isAnyKeyPressed = updatePipe2 = isDead = 0;

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
    if (updatePipe2 == 0 && botPipe[0].getXpos() <= screenWIDTH / 2 - 35)
        updatePipe2 = 1;
    if (updatePipe2)
    {
        botPipe[1].botPipeUpdate();
        topPipe[1].topPipeUpdate();
    }

    isDead = Game::detectCollision();
}

void Game::Event()
{
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT || isDead)
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

bool Game::detectCollision()
{
    SDL_Rect Bird = player.getDest();
    int bX1 = Bird.x, bX2 = bX1 + 19, bY1 = Bird.y, bY2 = bY1 + 16;
    for (int i = 0; i < 2; i++)
    {
        SDL_Rect Pipe = botPipe[i].getDest();
        // detect collision with bottom pipe
        int y1 = Pipe.y, y2 = y1 + Pipe.h, x1 = Pipe.x, x2 = x1 + Pipe.w;
        if (bX2 >= x1 && bX2 <= x2 && bY2 >= y1 && bY2 <= y2)
            return 1;

        // detect collision with top pipe
        Pipe = topPipe[i].getDest();
        y1 = Pipe.y, y2 = y1 + Pipe.h, x1 = Pipe.x, x2 = x1 + Pipe.w;
        if (bX2 >= x1 && bX2 <= x2 && bY1 >= y1 && bY1 <= y2)
            return 1;
    }
    return 0;
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