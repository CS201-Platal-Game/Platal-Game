#include "font_manager.h"

FontManager* FontManager::myInstance = 0;

bool FontManager::Load(std::string id, std::string filename, int ptsize) {
    TTF_Font* font;

    font = TTF_OpenFont(filename.c_str(), ptsize);
    if (!font){
        std::cout << "couldn't load " << id << " font" << std::endl;
        return false;
    }

    fontMap[id] = font;
    return true;
}


void FontManager::Draw(std::string id, std::string txt, int x, int y,
                       SDL_Color color, SDL_Renderer * renderer) {
    SDL_Rect dest = { x, y, 300, 50 };

    // TODO: compute the appropriate width of the font lol

    // create the texture
    SDL_Surface* surface;
    surface = TTF_RenderText_Solid(fontMap[id], txt.c_str(), color);
    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);


    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_DestroyTexture(texture);
}


void FontManager::Exterminate(std::string id) {
    //TTF_CloseFont(fontMap[id]);
    fontMap.erase(id);
}


void FontManager::Clean() {
    TTF_Font* font;
    auto iter = fontMap.begin();
    while (iter != fontMap.end()) {
        font = iter->second;
        TTF_CloseFont(font);
        iter++;
    }
}