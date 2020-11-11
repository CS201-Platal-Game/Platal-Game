#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>

class Game {
  public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() { return isrunning; }

    static SDL_Renderer* renderer;

  private:
    bool isrunning;
    int count = 0;
    SDL_Window* window;
};
