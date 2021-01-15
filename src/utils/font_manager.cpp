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
    //SDL_Rect dest = {x, y, txt.length()*(size/2), size};

    // TODO: compute the appropriate width of the font lol -done

    // create the texture
    SDL_Surface* surface;
    surface = TTF_RenderText_Solid(fontMap[id], txt.c_str(), color);
    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    int width = 0;
    int height = 0;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    SDL_Rect dest = {x, y, width, height};

    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_DestroyTexture(texture);
}

void FontManager::DrawBold(std::string id, std::string txt, int x, int y,
                       SDL_Color color, SDL_Renderer * renderer) {
    //SDL_Rect dest = {x, y, txt.length()*(size/2), size};

    // TODO: compute the appropriate width of the font lol -done

    // create the texture
    SDL_Surface* surface;

    TTF_SetFontStyle(fontMap[id], TTF_STYLE_BOLD);
    surface = TTF_RenderText_Solid(fontMap[id], txt.c_str(), color);
    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    int width = 0;
    int height = 0;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    SDL_Rect dest = {x, y, width, height};

    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_DestroyTexture(texture);
    TTF_SetFontStyle(fontMap[id], TTF_STYLE_NORMAL);
}

void FontManager::DrawIt(std::string id, std::string txt, int x, int y,
                           SDL_Color color, SDL_Renderer * renderer) {
    //SDL_Rect dest = {x, y, txt.length()*(size/2), size};

    // TODO: compute the appropriate width of the font lol -done

    // create the texture
    SDL_Surface* surface;

    TTF_SetFontStyle(fontMap[id], TTF_STYLE_ITALIC);
    surface = TTF_RenderText_Solid(fontMap[id], txt.c_str(), color);
    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    int width = 0;
    int height = 0;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    SDL_Rect dest = {x, y, width, height};

    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_DestroyTexture(texture);
    TTF_SetFontStyle(fontMap[id], TTF_STYLE_NORMAL);
}

int FontManager::RenderWidth(std::string font_id, std::string txt) {
    int w, h;
    TTF_SizeText(fontMap[font_id], txt.c_str(), &w, &h);
    return w;
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