#include "TextObject.h"

SDL_Texture *TextObject::getTexture()
{
    return Texture;
}

void TextObject::CreateText(SDL_Renderer *ren, TTF_Font *font, SDL_Color color)
{
    if (font == NULL)
        cout << "Invalid font " << SDL_GetError() << '\n';
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "0", color);
    if (textSurface == NULL)
        cout << "Cannot render text: " << TTF_GetError() << '\n';
    Texture = SDL_CreateTextureFromSurface(ren, textSurface);
    if (Texture == NULL)
        cout << "Cannot create texture from surface " << SDL_GetError() << '\n';
    SDL_FreeSurface(textSurface);
}

void TextObject::Render(SDL_Renderer *ren)
{
    SDL_RenderCopy(ren, getTexture(), NULL, &getDest());
}