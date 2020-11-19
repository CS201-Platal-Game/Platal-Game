#include "game.h"

void Game::HandleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
    case SDL_QUIT:
        is_running_ = false;
        break;
    default:
        break;
    }
}
