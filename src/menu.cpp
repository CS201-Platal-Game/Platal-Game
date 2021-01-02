#include "menu.h"
#include "game.h"

void Menu::Quit() {
    Game::game_state_ = kQuit;
}

void Menu::HandleInput(SDL_Event event) {
    switch (event.key.keysym.sym) {
    case SDLK_RETURN:
        Quit();
        break;
    case SDLK_LSHIFT:
        Game::game_state_ = kWorld;
        break;
    default:
        break;
    }
}

void Menu::Render() {
    SDL_Rect menu_rect = {0, 460, 800, 240};
    SDL_SetRenderDrawBlendMode(Game::renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Game::renderer_, 0, 0, 0, 196);
    SDL_RenderFillRect(Game::renderer_, &menu_rect);

    FontManager::Instance()->Draw("retganon", "Menu", 20, 480,
                                  {200, 50, 50}, Game::renderer_);

    FontManager::Instance()->Draw("retganon", "Quit", 20, 530,
                                  {175, 175, 255}, Game::renderer_);
}
