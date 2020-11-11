#pragma once
#include "Game.h"

class TextureManager {
  public:
    static SDL_Texture* LoadTexture(const char* filename);
    static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
};