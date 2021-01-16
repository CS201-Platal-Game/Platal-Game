#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <map>
#include <string>

#ifndef PLATAL_GAME_TEXTURE_MANAGER_H
#define PLATAL_GAME_TEXTURE_MANAGER_H

class TextureManager {
  public:
    static TextureManager* Instance() {
        if (myInstance == 0) {
            myInstance = new TextureManager();
        }
        return myInstance;
    }

    //initialiser
    bool Load(std::string id, std::string filename, SDL_Renderer* renderer); //load the element so we are able to reference it later

    // to draw static objects like the background image
    void Draw(std::string id,
              SDL_Rect src_, SDL_Rect dest_,
              SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    // to draw animated objects and characters (can also be used to draw tiled objects)
    // the frames thing is to facilitate animation of characters (think of a GIF, but as one long image with multiple frames)
    void DrawFrame(std::string id,
                   SDL_Rect src, SDL_Rect dest,
                   SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    // delete SDL texture (yes this is a doctor who reference)
    void exterminate(std::string id);

    ~TextureManager() { myInstance->Clean(); };
    void Clean();

  private:
    std::map<std::string, SDL_Texture*> textureMap; // map with all SDL textures
    TextureManager() = default;
    static TextureManager* myInstance;
};

#endif