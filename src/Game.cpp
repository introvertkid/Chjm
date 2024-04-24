#include "Game.h"

Game::Game()
{
    window = NULL;
    renderer = NULL;
    gameState = isAnyKeyPressed = updatePipe2 = isDead = score = 0;

    player.setSrc(0, 0, 19, 16);
    player.setDest(screenWIDTH / 2, screenHEIGHT / 2, 50, 50);

    for (int i = 0; i < 2; i++)
    {
        topPipe[i].setSrc(0, 0, 25, 100);
        botPipe[i].setSrc(0, 0, 25, 100);
    }
    botPipe[0].initPipeHeight();
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
    if (TTF_Init() < 0)
    {
        cout << "Cannot initialize TTF" << SDL_GetError() << '\n';
    }
    else
    {
        scoreFont = TTF_OpenFont("TextFont/flappy-font.ttf", 24);
        if (scoreFont == NULL)
            cout << "Cannot open font: " << SDL_GetError() << '\n';

        Message.CreateText(renderer, scoreFont, blackColor);
        Message.setSrc(0, 0, 0, 0);
        Message.setDest(screenWIDTH / 2 - 25, 0, 50, 50);
    }
}

void Game::Update()
{
    player.Update();

    botPipe[0].Update(0, 0);
    topPipe[0].Update(0, 1);
    if (updatePipe2 == 0 && botPipe[0].getXpos() <= screenWIDTH / 2 - 35)
    {
        updatePipe2 = 1;
    }

    if (updatePipe2)
    {
        botPipe[1].Update(1, 0);
        topPipe[1].Update(1, 1);
    }

    isDead = detectCollision();
    if (isDead)
    {
        gameState = 0;
        return;
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

    if (Message.getTexture() == NULL)
        cout << "vcl" << '\n';
    Message.Render(renderer);
    // SDL_RenderCopy(renderer, Message.getTexture(), NULL, &Message.getDest());

    SDL_RenderPresent(renderer);
}

bool Game::detectCollision()
{
    SDL_Rect Bird = player.getDest();
    int bX1 = Bird.x, bX2 = bX1 + 50, bY1 = Bird.y, bY2 = bY1 + 50;
    if (bY1 <= 0 || bY2 >= screenHEIGHT)
        return 1;
    for (int i = 0; i < 2; i++)
    {
        SDL_Rect Pipe = botPipe[i].getDest();
        // detect collision with bottom pipe
        int y1 = Pipe.y, y2 = y1 + Pipe.h, x1 = Pipe.x, x2 = x1 + Pipe.w;
        if (bX2 >= x1 && bX2 <= x2 && bY2 >= y1)
            return 1;

        // detect collision with top pipe
        Pipe = topPipe[i].getDest();
        y1 = Pipe.y, y2 = y1 + Pipe.h, x1 = Pipe.x, x2 = x1 + Pipe.w;
        if (bX2 >= x1 && bX2 <= x2 && bY1 <= y2)
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
    IMG_Quit();
    TTF_Quit();
}

bool Game::getGameState()
{
    return gameState;
}