#include "Game.h"
#include <SDL2/SDL.h>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;

Game* game = nullptr;

int main(int argc, char* argv[]) {
    // FPS LIMITER
    const int fps = 60;
    const int frameDelay = 1000 / fps;
    int frameStart;
    int frameTime;

    game = new Game();
    game->init("map_test",
               SDL_WINDOWPOS_CENTERED,
               SDL_WINDOWPOS_CENTERED,
               SCREEN_WIDTH,
               SCREEN_HEIGHT,
               false);

    while (game->running()) {
        frameStart = SDL_GetTicks(); // start chrono

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart; //end chrono

        if (frameDelay > frameTime) // delay if game runs too fast
            SDL_Delay(frameDelay - frameTime);
    }

    game->clean();
    return 0;
}
