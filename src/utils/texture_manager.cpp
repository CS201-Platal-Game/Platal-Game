#include "texture_manager.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <iostream>

bool TextureManager::load(std::string id, std::string filename, SDL_renderer* renderer){
    // I could use const char* here but I've decided this is easier since my input filename is a string
    SDL_Surface* TempSurface = IMG_Load(filename.c_str());

    if (TempSurface == 0){ // if stuff ain't workinnn
        std::cout << "Error loading file: " << filename << std::endl;
        return false;
    }
    // if stuff IS working then...
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TempSurface);

    return true;
}
