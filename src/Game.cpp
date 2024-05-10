#include "Game.h"

Game::Game()
{
    window = NULL;
    renderer = NULL;
    gameState = isAnyKeyPressed = updatePipe2 = isDead = score = isPlaying = 0;

    player.setSrc(0, 0, 19, 16);
    player.setDest(screenWIDTH / 2, screenHEIGHT / 2, 50, 50);

    ground.setSrc(0, 0, 540, 120);

    for (int i = 0; i < 2; i++)
    {
        topPipe[i].setSrc(0, 0, 25, 100);
        botPipe[i].setSrc(0, 0, 25, 100);
        botPipe[i].initPipeHeight(i);
    }

    for (int i = 0; i < 3; i++)
    {
        buttons[i].setSrc(0, 0, 49, 21);
    }
    buttons[PLAY].setDest(160, 200, 170, 80);
    buttons[OPTIONS].setDest(160, 300, 170, 80);
    buttons[EXIT].setDest(160, 400, 170, 80);
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
                ground.CreateTexture("image/ground.png", renderer);
                for (int i = 0; i < 2; i++)
                {
                    topPipe[i].CreateTexture("image/topPipe.png", renderer);
                    botPipe[i].CreateTexture("image/botPipe.png", renderer);
                }

                buttons[PLAY].CreateTexture("image/playButtonUI.png", renderer);
                buttons[OPTIONS].CreateTexture("image/optionsButtonUI.png", renderer);
                buttons[EXIT].CreateTexture("image/exitButtonUI.png", renderer);
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

        scoreText.CreateText(renderer, scoreFont, blackColor, to_string(score));
        scoreText.setDest(screenWIDTH / 2 - 25, 0, 50, 50);
    }

    if (Mix_Init(1) == 0)
    {
        cout << "Couldn't initialize mixer " << Mix_GetError() << '\n';
    }
    else
    {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 120) < 0)
            std::cout << "Error:" << Mix_GetError() << '\n';

        wingSound = Mix_LoadWAV("sound/wingSound.wav");
        if (wingSound == NULL)
            cout << "vcl ne: " << Mix_GetError << '\n';
        hitSound = Mix_LoadWAV("sound/hitSound.wav");
        pointSound = Mix_LoadWAV("sound/pointSound.wav");
    }
}

void Game::Update()
{
    int xMouse = 0, yMouse = 0;
    SDL_GetMouseState(&xMouse, &yMouse);
    // cout << xMouse << " " << yMouse << '\n';

    ground.Update();

    for (int i = 0; i < 3; i++)
    {
        if (insideButton(buttons[i]))
        {
            buttons[i].setSrc(49, 0, 49, 21);
        }
        else
            buttons[i].setSrc(0, 0, 49, 21);
    }

    if (isPlaying)
    {
        player.Update();

        for (int i = 0; i < 2; i++)
        {
            botPipe[i].Update(i, 0);
            topPipe[i].Update(i, 1);
        }

        isDead = detectCollision();
        if (isDead)
        {
            // gameState = 0;
            newGame();
            isPlaying = 0;
            return;
        }

        // update score ?
        for (int i = 0; i < 2; i++)
        {
            if (Xpos[i] + 70 < player.getDest().x && botPipe[i].GetPassedState() == 0)
            {
                score++;
                botPipe[i].SetPassedState();
                scoreText.CreateText(renderer, scoreFont, blackColor, to_string(score));
            }
        }
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
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (!isPlaying)
        {
            if (insideButton(buttons[PLAY]))
            {
                isPlaying = 1;
            }
            else if (insideButton(buttons[OPTIONS]))
            {
            }
            else if (insideButton(buttons[EXIT]))
            {
                gameState = 0;
                return;
            }
        }
    }
    if (event.type == SDL_KEYDOWN)
    {
        isAnyKeyPressed = 1;
        if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_SPACE)
        {
            if (!player.isJumping())
            {
                player.Jump();
                // Mix_VolumeChunk(wingSound, 20);
                Mix_PlayChannel(1, wingSound, 0);
            }
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
    ground.Render(renderer);

    if (!isPlaying)
    {
        for (int i = 0; i < 3; i++)
            buttons[i].Render(renderer);
    }
    else
    {
        player.Render(renderer);

        for (int i = 0; i < 2; i++)
        {
            botPipe[i].Render(renderer);
            topPipe[i].Render(renderer);
        }

        scoreText.Render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::newGame()
{
    isAnyKeyPressed = updatePipe2 = isDead = score = 0;
    scoreText.CreateText(renderer, scoreFont, blackColor, to_string(score));

    for (int i = 0; i < 2; i++)
    {
        botPipe[i].initPipeHeight(i);
    }
    player.setDest(screenWIDTH / 2, screenHEIGHT / 2, 50, 50);
}

bool Game::detectCollision()
{
    SDL_Rect Bird = player.getDest();
    int bX1 = Bird.x, bX2 = bX1 + 48, bY1 = Bird.y, bY2 = bY1 + 48;
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

bool Game::insideButton(Button but)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Rect mouse = but.getDest();
    int x1 = mouse.x, x2 = x1 + mouse.w, y1 = mouse.y, y2 = y1 + mouse.h;
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
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
    Mix_Quit();
}

bool Game::getGameState()
{
    return gameState;
}