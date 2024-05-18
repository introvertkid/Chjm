#include "Game.h"

Game::Game()
{
    window = NULL;
    renderer = NULL;
    gameState = isAnyKeyPressed = isDead = score = isPlaying = showPrompt = 0;

    player.setSrc(0, 0, 19, 16);
    player.setDest(screenWIDTH / 2, screenHEIGHT / 2, 50, 50);

    prompt.setSrc(0, 0, 507, 102);
    prompt.setDest(70, 250, 350, 100);

    Highscore.setSrc(0, 0, 444, 282);

    gr1.setSrc(0, 0, 540, 120);
    gr2.setSrc(0, 0, 540, 120);
    gr1.setXpos(0);
    gr2.setXpos(480);

    for (int i = 0; i < 2; i++)
    {
        topPipe[i].setSrc(0, 0, 25, 100);
        botPipe[i].setSrc(0, 0, 25, 100);
        botPipe[i].initPipeHeight(i);
    }

    for (int i = 0; i < 4; i++)
    {
        buttons[i].setSrc(0, 0, 49, 21);
    }
    buttons[HOWTOPLAY].setSrc(0, 0, 10, 15);

    buttons[HOWTOPLAY].setDest(10, 580, 40, 60);
    buttons[PLAY].setDest(160, 200, 170, 80);
    buttons[OPTIONS].setDest(160, 300, 170, 80);
    buttons[EXIT].setDest(160, 400, 170, 80);
    buttons[REPLAY].setDest(95, 500, 170, 80);
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
                gr1.CreateTexture("image/ground.png", renderer);
                gr2.CreateTexture("image/ground.png", renderer);
                prompt.CreateTexture("image/prompt.png", renderer);
                Highscore.CreateTexture("image/highscore.png", renderer);
                for (int i = 0; i < 2; i++)
                {
                    topPipe[i].CreateTexture("image/topPipe.png", renderer);
                    botPipe[i].CreateTexture("image/botPipe.png", renderer);
                }

                buttons[PLAY].CreateTexture("image/playButtonUI.png", renderer);
                buttons[OPTIONS].CreateTexture("image/optionsButtonUI.png", renderer);
                buttons[EXIT].CreateTexture("image/exitButtonUI.png", renderer);
                buttons[REPLAY].CreateTexture("image/replayButtonUI.png", renderer);
                buttons[HOWTOPLAY].CreateTexture("image/HowToPlayButtonUI.png", renderer);
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
        scoreText.setDest(screenWIDTH / 2 - 25, 5, 50, 50);
    }

    if (Mix_Init(1) == 0)
    {
        cout << "Couldn't initialize mixer " << Mix_GetError() << '\n';
    }
    else
    {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            cout << "Error:" << Mix_GetError() << '\n';

        wingSound = Mix_LoadWAV("sound/wingSound.wav");
        hitSound = Mix_LoadWAV("sound/hitSound.wav");
        pointSound = Mix_LoadWAV("sound/pointSound.wav");
    }
}

void Game::Update()
{
    // int xMouse = 0, yMouse = 0;
    // SDL_GetMouseState(&xMouse, &yMouse);
    // cout << xMouse << " " << yMouse << '\n';

    gr1.Update(isPlaying & ~isDead);
    gr2.Update(isPlaying & ~isDead);

    for (int i = 0; i < 5; i++)
    {
        if (insideButton(buttons[i]))
        {
            if (i < 4)
                buttons[i].setSrc(49, 0, 49, 21);
            else
                buttons[i].setSrc(10, 0, 10, 15);
        }
        else
        {
            if (i < 4)
                buttons[i].setSrc(0, 0, 49, 21);
            else
                buttons[i].setSrc(0, 0, 10, 15);
        }
    }

    if (isPlaying)
    {
        player.Update();

        if (!isDead)
        {
            for (int i = 0; i < 2; i++)
            {
                botPipe[i].Update(i, 0);
                topPipe[i].Update(i, 1);
            }

            isDead = detectCollision();
            if (isDead)
            {
                Mix_PlayChannel(-1, hitSound, 0);
                // newGame();
                // isPlaying = 0;
                return;
            }

            // update score ?
            for (int i = 0; i < 2; i++)
            {
                if (botPipe[i].getXpos(i) + 70 < player.getDest().x && botPipe[i].GetPassedState() == 0)
                {
                    Mix_PlayChannel(-1, pointSound, 0);
                    score++;
                    botPipe[i].SetPassedState();
                    scoreText.CreateText(renderer, scoreFont, blackColor, to_string(score));
                }
            }
        }
    }
    else
    {
        if (showPrompt)
        {
            prompt.Update();
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
        if (showPrompt)
        {
            showPrompt = 0;
            return;
        }
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
            else if (insideButton(buttons[HOWTOPLAY]))
            {
                showPrompt = 1;
            }
        }
        else
        {
            if (insideButton(buttons[REPLAY]))
            {
                newGame();
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
                Mix_PlayChannel(-1, wingSound, 0);
            }
            else
                player.Gravity();
        }
    }
    else if (isPlaying && !isDead)
        player.Gravity();
}

void Game::Render()
{
    SDL_RenderClear(renderer);

    bg.Render(renderer);
    gr1.Render(renderer);
    gr2.Render(renderer);

    if (!isPlaying)
    {
        if (showPrompt)
        {
            prompt.Render(renderer);
        }
        else
        {
            for (int i = 0; i < 3; i++)
                buttons[i].Render(renderer);
            buttons[HOWTOPLAY].Render(renderer);
        }
    }
    else
    {
        player.Render(renderer);
        if (isDead)
        {
            ifstream fi("best.txt");
            int best;
            fi >> best;
            best = max(best, score);
            fi.close();

            ofstream fo("best.txt");
            fo << best;
            fo.close();

            HighscoreText.CreateText(renderer, scoreFont, blackColor, to_string(best));
            HighscoreText.setDest(315, 215, 50, 50);
            scoreText.setDest(150, 240, 60, 80);
            Highscore.setDest(50, 90, 400, 400);

            Highscore.Render(renderer);
            HighscoreText.Render(renderer);
            buttons[REPLAY].Render(renderer);
        }
        else
        {
            for (int i = 0; i < 2; i++)
            {
                botPipe[i].Render(renderer);
                topPipe[i].Render(renderer);
            }
        }

        scoreText.Render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::newGame()
{
    isAnyKeyPressed = isDead = score = 0;
    scoreText.CreateText(renderer, scoreFont, blackColor, to_string(score));

    player.setDest(screenWIDTH / 2, screenHEIGHT / 2, 50, 50);
    scoreText.setDest(screenWIDTH / 2 - 25, 5, 50, 50);

    for (int i = 0; i < 2; i++)
    {
        botPipe[i].initPipeHeight(i);
        botPipe[i].Update(i, 0);
        topPipe[i].Update(i, 1);
    }
}

bool Game::detectCollision()
{
    SDL_Rect Bird = player.getDest();
    int bX1 = Bird.x, bX2 = bX1 + 50, bY1 = Bird.y, bY2 = bY1 + 50;
    if (bY1 <= -5 || bY2 >= 545)
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