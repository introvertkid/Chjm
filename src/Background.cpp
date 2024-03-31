#include "Background.h"

void Background::Render(SDL_Renderer *ren, SDL_Texture *Texture)
{
    SDL_RenderCopy(ren, Texture, NULL, NULL);
}

void Background::Render(SDL_Renderer *ren, SDL_Texture *Texture, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(ren, Texture, &src, &src);
}