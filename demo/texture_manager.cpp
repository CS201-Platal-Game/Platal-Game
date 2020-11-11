#include "texture_manager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
    SDL_Surface* tempsurface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer_, tempsurface);
    SDL_FreeSurface(tempsurface);

    return tex;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(Game::renderer_, texture, &src, &dest);
}
