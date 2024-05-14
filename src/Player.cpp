#include "Player.h"

void Player::Update()
{
    animationFrame++;
    animationFrame %= 24;
    setSrc(animationFrame / 12 * 19, 0, 19, 16);
}

void Player::Gravity()
{
    accelerator += 0.05;
    if (isJumping())
    {
        jumpHeight += gravity;
        Ypos += (accelerator + jumpHeight);
        if (jumpHeight > 0)
        {
            jumpState = 0;
            jumpHeight = -5;
        }
    }
    else
    {
        Ypos += (accelerator + gravity);
    }
    // Ypos = min((int)Ypos, screenHEIGHT);
    setDest(screenWIDTH / 2, Ypos, 50, 50);
}

void Player::Jump()
{
    currentJumpTimer = SDL_GetTicks();
    if (currentJumpTimer - lastJumpTimer > 30)
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

bool Player::isJumping()
{
    return jumpState;
}