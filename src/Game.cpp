#include "Game.h"
#include "TextureManager.h"
#include "map.h"

Map* map;

SDL_Renderer* Game::renderer = nullptr;

Game::Game() {
    isrunning = false;
}

Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0 &&
        IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG) {
        std::cout << "subsystem initialized..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
            std::cout << "window created..." << std::endl;

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "renderer created..." << std::endl;
        }

        isrunning = true;
    } else
        isrunning = false;

    map = new Map();
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
    case SDL_QUIT:
        isrunning = false;
        break;
    default:
        break;
    }
}

void Game::update() {}

void Game::render() {
    SDL_RenderClear(renderer);
    // where we add stuff to render
    map->DrawMap();

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_QUIT;
    std::cout << "Game cleaned..." << std::endl;
}