#include "game.h"
#include "map.h"
#include "texture_manager.h"

Map* map;

SDL_Renderer* Game::renderer_ = nullptr;

Game::Game() { is_running_ = false; }

Game::~Game() {}

void Game::Init(const char* title, int xpos, int ypos, int width, int height,
                bool fullscreen) {
    int flags = 0;
    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0 &&
        IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG) {
        std::cout << "subsystem initialized..." << std::endl;

        window_ = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window_)
            std::cout << "window created..." << std::endl;

        renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
        if (renderer_) {
            SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
            std::cout << "renderer created..." << std::endl;
        }

        is_running_ = true;
    } else
        is_running_ = false;

    map = new Map();
}

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

void Game::Update() {}

void Game::Render() {
    SDL_RenderClear(renderer_);
    // where we add stuff to render
    map->DrawMap();

    SDL_RenderPresent(renderer_);
}

void Game::Clean() {
    SDL_DestroyWindow(window_);
    SDL_DestroyRenderer(renderer_);
    std::cout << "Game cleaned..." << std::endl;
}
