#define SDL_MAIN_HANDLED
#include "game.h"
#include <iostream>
// screen dimension constants
const int SCREEN_WIDTH = 896;
const int SCREEN_HEIGHT = 640;

Game* game = nullptr;

int main(void) {
    std::cout << "Platal Game" << std::endl;

    // fps limiter
    const int fps = 60;
    const int frameDelay = 1000 / fps;
    int frameStart;
    int frameTime;

    game = new Game();
    game->Init("map_test",
               SDL_WINDOWPOS_CENTERED,
               SDL_WINDOWPOS_CENTERED,
               SCREEN_WIDTH,
               SCREEN_HEIGHT,
               false);

    while (game->Running()) {
        frameStart = SDL_GetTicks(); // start chrono

        game->HandleEvents();
        game->Update();
        game->Render();

        frameTime = SDL_GetTicks() - frameStart; //end chrono
				
        if (frameDelay > frameTime) // delay if game runs too fast
            SDL_Delay(frameDelay - frameTime - 5);

	frameTime = SDL_GetTicks() - frameStart;
	game->DisplayFps(static_cast<int>(1000.0 / frameTime));
	game->Show();
    }

    delete game;
    return 0;
}
