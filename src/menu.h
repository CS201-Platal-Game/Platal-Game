#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "utils/font_manager.h"
#include <string>
#include <vector>

class MainMenu {
  public:
    MainMenu();
    void Continue();
    void Quit();
    void Render();
    void HandleInput(SDL_Event event);

  private:
    std::vector<std::string> options_ = {"Continue", "Quit"};
    size_t selected_option_ = 0;
};
