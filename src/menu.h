#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "utils/font_manager.h"
#include <string>

class MenuOption {
  public:
  private:
};

class Menu {
  public:
    void Quit();
    void Render();
    void HandleInput(SDL_Event event);

  private:
};
