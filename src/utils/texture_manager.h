#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class texture_manager {
  public:
    static SDL_Texture* LoadTexture(const char* filename);

    // take src rect from texture and draw it in the dest rect location
    static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
};
