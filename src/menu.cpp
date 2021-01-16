#include "menu.h"
#include "game.h"

MainMenu::MainMenu() {}

void MainMenu::Continue() { Game::game_state_ = kWorld; }

void MainMenu::DialogueDemo() { Game::game_state_ = kDialogue; }

void MainMenu::Synapses() { Game::game_state_ = kSynapses; }

void MainMenu::Quit() { Game::game_state_ = kQuit; }

void MainMenu::HandleInput(SDL_Event event) {
    switch (event.key.keysym.sym) {
    case SDLK_RETURN:
        switch (selected_option_) {
        case 0:
            Continue();
            break;
        case 1:
            DialogueDemo();
            break;
        case 2:
            Synapses();
            break;
        case 3:
            Quit();
            break;
        default:
            break;
        }
        break;
    case SDLK_LEFT:
        selected_option_ -= (selected_option_ > 0);
        break;
    case SDLK_RIGHT:
        selected_option_ += (selected_option_ < options_.size() - 1);
        break;
    default:
        break;
    }
}

void MainMenu::Render() {
    SDL_Rect menu_rect = {0, 460, 896, 240};

    SDL_SetRenderDrawBlendMode(Game::renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Game::renderer_, 0, 0, 0, 196);
    SDL_RenderFillRect(Game::renderer_, &menu_rect);

    FontManager::Instance()->Draw("retganon", "Menu", 20, 480, {200, 50, 50},
                                  Game::renderer_);
    int draw_x = 0, draw_y = 530;
    for (size_t i = 0; i < options_.size(); ++i) {
        draw_x += 20;

        std::string current_option = options_[i];
        SDL_Color color = {255, 255, 255};
        if (i == selected_option_) {
            color = {175, 175, 255};
        }

        FontManager::Instance()->Draw("retganon", current_option, draw_x,
                                      draw_y, color, Game::renderer_);

        draw_x += current_option.size() * 25;
    }
}
