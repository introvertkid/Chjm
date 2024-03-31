#include "Player.h"

void Player::Render(SDL_Renderer *ren, SDL_Texture *Texture, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(ren, Texture, &src, &dest);
}