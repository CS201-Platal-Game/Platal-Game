#pragma once
#include "SDL2/SDL.h"
#include <vector>

std::vector<SDL_Rect> GetTiles(SDL_Rect hitbox);

template <typename T> std::vector<SDL_Rect> GetTiles(T item) {
    std::vector<SDL_Rect> out;
    SDL_Rect hitbox = item.GetHitbox();
    for (int x = 0; x < hitbox.w; x += 64) {
        for (int y = 0; y < hitbox.h; y += 64) {
            int newX = (hitbox.x + x) / 64;
            int newY = (hitbox.y + y) / 64;
            out.push_back({newX, newY, 64, 64});
        }
    }
    return out;
}