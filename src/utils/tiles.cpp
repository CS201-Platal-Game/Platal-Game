#include "tiles.h"

std::vector<SDL_Rect> GetTiles(SDL_Rect hitbox) {
    std::vector<SDL_Rect> out;
    for (int x = 0; x < hitbox.w; x += 64) {
        for (int y = 0; y < hitbox.h; y += 64) {
            int newX = (hitbox.x + x) / 64;
            int newY = (hitbox.y + y) / 64;
            out.push_back({newX, newY, 64, 64});
        }
    }
    return out;
}