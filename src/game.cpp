#include "game.h"
#include "platal_map.h"
#include "utils/texture_manager.h"
#include "utils/font_manager.h"
#include "SDL2/SDL_ttf.h"

// static members definition
SDL_Renderer* Game::renderer_ = nullptr;

Game::Game() {
    is_running_ = false;
}

Game::~Game() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    // need to add the delete map
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    std::cout << "game cleaned" << std::endl;
}

void Game::Init(const char* title, int xpos, int ypos, int width, int height,
                bool fullscreen) {
    int flags = 0;
    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0 &&
        IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG &&
        TTF_Init() == 0) {
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
    current_map_ = new Map();

    // create the game character
    // might need to store that on the heap
    player_ = new Protagonist("player", { width/2, height/2 });
}

void Game::HandleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
    case SDL_QUIT:
        is_running_ = false;
        break;
    case SDL_KEYDOWN:
        player_->HandleInput(event);
        break;
    case SDL_KEYUP:
        break;
    // New case to be added for the implementation of the character interaction with the object
    default:
        // to be extended once the facilities to handle user input have been created
        break;
    }
}

void Game::Update() {
    // update player
    player_->Move();
}

void Game::Render() {
    SDL_RenderClear(renderer_);
    // where we add stuff to render in rendering order {map -> chars -> menus}
    current_map_->DrawMap(player_->GetPosition());

    // begin font demo
    FontManager::Instance()->Load("retganon", "./fonts/retganon.ttf", 16);
    FontManager::Instance()->Draw("retganon", "PLATAL GAME!", 250, 250,
                                  {200, 50, 50}, renderer_);
    FontManager::Instance()->Exterminate("retganon");
    // end font demo


    SDL_RenderPresent(renderer_);
}