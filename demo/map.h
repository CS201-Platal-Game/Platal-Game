#pragma once
#include "game.h"

class Map {
  public:
    Map();
    ~Map();

    void LoadMap(int arr[20][25]);
    void DrawMap();

  private:
    SDL_Rect src_, dest_;
    SDL_Texture *dirt_, *grass_, *water_;
    int map_[20][25];
};
