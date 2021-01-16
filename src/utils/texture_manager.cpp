#include "texture_manager.h"

TextureManager* TextureManager::myInstance = 0;

bool TextureManager::Load(std::string id, std::string filename, SDL_Renderer* renderer) {
    // I could use const char* here but I've decided this is easier since my input filename is a string
    SDL_Surface* TempSurface = IMG_Load(filename.c_str());

    if (TempSurface == 0) { // if stuff ain't workinnn
        std::cout << "Error loading file: " << filename << std::endl;
        return false;
    }
    // if stuff IS working then...
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TempSurface);

    SDL_FreeSurface(TempSurface); //delete the temp surface

    //exception handlers:
    if (texture == 0) {
        std::cout << "Error creating texture, filename:" << filename << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    textureMap[id] = texture; //save the texture in the map data structure by inserting it at position id
    // a map is the equivalent of a python dictionary
    return true;
}

void TextureManager::Draw(std::string id, SDL_Rect src, SDL_Rect dest, SDL_Renderer* renderer, SDL_RendererFlip flip) {
    // this does the same as RenderCopy but has more parameters
    // copies a portion of the texture to current rendering target (w/ rotation and/or flip around a given origin)
    SDL_RenderCopyEx(renderer, textureMap[id], &src, &dest, 0, 0, flip);
}

void TextureManager::DrawFrame(std::string id, SDL_Rect src, SDL_Rect dest, SDL_Renderer* renderer, SDL_RendererFlip flip) {
    // this does the same as RenderCopy but has more parameters
    // copies a portion of the texture to current rendering target (w/ rotation and/or flip around a given origin)
    SDL_RenderCopyEx(renderer, textureMap[id], &src, &dest, 0, 0, flip);
}

void TextureManager::exterminate(std::string id) {
    textureMap.erase(id);
}

void TextureManager::Clean() {
    SDL_Texture* texture;
    auto iter = textureMap.begin();
    while (iter != textureMap.end()) {
        texture = iter->second;
        SDL_DestroyTexture(texture);
        iter++;
    }
}
