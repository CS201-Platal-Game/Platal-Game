#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>

class Game {
  public:
    Game();
    ~Game();

    void Init(const char* title, int xpos, int ypos, int width, int height,
              bool fullscreen);

    void HandleEvents();
    void Update();
    void Render();
    void Clean();

    bool Running() { return is_running_; }

    static SDL_Renderer* renderer_;

  private:
    bool is_running_;
    int count_ = 0;
    SDL_Window* window_;
};
