#include "Player.h"

void Player::Update()
{
    animationFrame++;
    animationFrame %= 24;
    setSrc(animationFrame / 12 * playerWidth, 0, playerWidth, playerHeight);
}

void Player::Gravity()
{
    accelerator += 0.07;
    if (isJumping())
    {
        jumpHeight += gravity;
        Ypos += (accelerator + jumpHeight);
        if (jumpHeight > 0)
        {
            jumpState = 0;
            jumpHeight = -6;
        }
    }
    else
    {
        Ypos += (accelerator + gravity);
    }
    Ypos = min((int)Ypos, screenHEIGHT);
    setDest(screenWIDTH / 2, Ypos, 50, 50);
}

void Player::Jump()
{
    currentJumpTimer = SDL_GetTicks();
    if (currentJumpTimer - lastJumpTimer > 120)
    {
        accelerator = 0;
        jumpState = 1;
        lastJumpTimer = currentJumpTimer;
    }
    else
    {
        Gravity();
    }
}

void Player::Render(SDL_Renderer *ren)
{
    SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}

bool Player::isJumping()
{
    return jumpState;
}