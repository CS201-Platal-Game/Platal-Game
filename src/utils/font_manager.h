//
// Font manager class to ease out the process of loading and rendering fonts
//
#pragma once
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <map>

#ifndef PLATAL_GAME_FONT_MANAGER_H
#define PLATAL_GAME_FONT_MANAGER_H

class FontManager {
  public:
    static FontManager* Instance(){
        if (myInstance == 0)
            myInstance = new FontManager();
        return myInstance;
    }

    // loads a font element
    bool Load(std::string id, std::string filename, int ptsize);
    //bool Load(std::string id, std::string filename);

    void Draw(std::string id, std::string txt, int x, int y,
              SDL_Color, SDL_Renderer*);

    void Exterminate(std::string id);

  private:
    std::map<std::string, TTF_Font*> fontMap; // map with all the fonts
    FontManager() = default;
    ~FontManager();
    static FontManager* myInstance;
};

#endif // PLATAL_GAME_FONT_MANAGER_H
