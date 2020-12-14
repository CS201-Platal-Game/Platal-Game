#include "texture_manager.h"


// NOTE - This has not been tested yet because of the bugs
// and because I need help to run it from my linux virtual machine (I've forgotten how to)
// based on examples seen, will be debugged and further modified to fit our needs once I get a basic thing working
TextureManager* TextureManager::myInstance = 0;

bool TextureManager::load(std::string id, std::string filename, SDL_Renderer* renderer){
    // I could use const char* here but I've decided this is easier since my input filename is a string
    SDL_Surface* TempSurface = IMG_Load(filename.c_str());

    if (TempSurface == 0){ // if stuff ain't workinnn
        std::cout << "Error loading file: " << filename << std::endl;
        return false;
    }
    // if stuff IS working then...
    // there is an error with 'texture' - undeclared identifier, apparently
    // I have followed the syntax in from the SDL wiki page and I don't understand why this doesn't work
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TempSurface);

    //I'm just going to continue coding and fix it later
    SDL_FreeSurface(TempSurface); //delete the temp surface

    //exception handlers:
    if (texture == 0){
        std::cout << "Error creating texture, filename:" << filename << std::endl;
        return false;
    }

    //I'm also not sure why here it says textureMap is undeclared
    //Even though CLion recognises that it is declared in texture_manager.h
    textureMap[id] = texture; //save the texture in the map data structure by inserting it at position id
    // a map is the equivalent of a python dictionary
    return true;
}

void TextureManager::Draw(std::string id, SDL_Rect src, SDL_Rect dest, SDL_Renderer* renderer, SDL_RendererFlip flip) {
    // this does the same as RenderCopy but has more parameters
    // copies a portion of the texture to current rendering target (w/ rotation and/or flip around a given origin)
    SDL_RenderCopyEx(renderer, textureMap[id], &src, &dest, 0, 0, flip);
}

void TextureManager::DrawFrame(std::string id, SDL_Rect src, SDL_Rect dest, SDL_Renderer *renderer, SDL_RendererFlip flip) {
    // this does the same as RenderCopy but has more parameters
    // copies a portion of the texture to current rendering target (w/ rotation and/or flip around a given origin)
    SDL_RenderCopyEx(renderer, textureMap[id], &src, &dest, 0, 0, flip);

}

void TextureManager::exterminate(std::string id) {
    delete textureMap[id];
    textureMap.erase(id);
}

void TextureManager::Clean() {
    SDL_Texture* texture;
    auto iter = textureMap.begin();
    while(iter != textureMap.end())
    {
        texture = iter->second;
        SDL_DestroyTexture(texture);
        iter++;
    }


}


