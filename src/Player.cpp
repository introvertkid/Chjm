#include "Player.h"

void Player::Render(SDL_Renderer *ren)
{
    animationFrame++;
    animationFrame %= 24;
    setSrc(animationFrame / 12 * playerWidth, 0, playerWidth, playerHeight);
    SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}

void Player::Gravity()
{
    accelerator1 += 0.035;
    accelerator2 += 0.035;
    if (isJumping())
    {
        jumpHeight += gravity;
        Ypos += (accelerator1 + accelerator2 + jumpHeight);
        if (jumpHeight > 0)
        {
            jumpState = 0;
            jumpHeight = -6;
        }
    }
    else
    {
        Ypos += (accelerator1 + accelerator2 + gravity);
    }
    setDest(0, Ypos, 50, 50);
}

void Player::Jump()
{
    currentJumpTimer = SDL_GetTicks();
    if (currentJumpTimer - lastJumpTimer > 120)
    {
        accelerator1 = accelerator2 = 0;
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

// void Player::CreateTexture1(const char *path, SDL_Renderer *ren)
// {
//     Texture1 = TextureManager::Texture(path, ren);
// }

// void Player::CreateTexture2(const char *path, SDL_Renderer *ren)
// {
//     Texture2 = TextureManager::Texture(path, ren);
// }