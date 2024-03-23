#include "TextureManager.h"

SDL_Texture *TextureManager::Texture(const char *FileLocation, SDL_Renderer *ren)
{
    SDL_Surface *surface;
    surface = IMG_Load(FileLocation);
    if (surface == NULL)
        cout << "Unable to load image because SDL_image error" << IMG_GetError() << '\n';

    SDL_Texture *texture;
    texture = SDL_CreateTextureFromSurface(ren, surface);
    SDL_FreeSurface(surface);
    if (texture == NULL)
        cout << "Cannot create texture from surface" << '\n';
    return texture;
}