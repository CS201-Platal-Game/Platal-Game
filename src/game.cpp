#include "game.h"
#include "platal_map.h"
#include "utils/texture_manager.h"
#include "utils/font_manager.h"
#include "SDL2/SDL_ttf.h"

// static members definition
SDL_Renderer* Game::renderer_ = nullptr;
SDL_Window* Game::window_ = nullptr;
// this stays just in the unlikely case that we wish to make game a singleton
//Game* Game::myInstance = 0;

Game::Game() {
    is_running_ = false;
}

Game::~Game() {
    TextureManager::Instance()->Clean();//exterminate("player");
    std::cout << "cleaned textures" << std::endl;
    FontManager::Instance()->Clean();//->Exterminate("retganon");
    std::cout << "cleaned fonts" << std::endl;
    SDL_DestroyRenderer(renderer_);
    std::cout << "freed renderer" << std::endl;
    SDL_DestroyWindow(window_);
    std::cout << "freed window" << std::endl;
    // need to add the delete map
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    std::cout << "game cleaned" << std::endl;
}

void Game::Init(const char* title, int xpos, int ypos, int width, int height,
                bool fullscreen) {
    width_ = width;
    height_ = height;
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
            SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0);//255, 255, 255, 255);
            std::cout << "renderer created..." << std::endl;
        }

        is_running_ = true;
    } else
        is_running_ = false;
    current_map_ = new Map();
    // for the map positions, the y coordinate is weirdly shifted by -2 when compared to the csv...
    current_map_->LoadMap("./maps/room.csv", {3,5});

    // create the game character
    // might need to store that on the heap
    player_ = new Protagonist("player", { width/2, height/2 });
    TextureManager::Instance()->load("player", "./images/sprites/littleman1.png", renderer_);
    FontManager::Instance()->Load("retganon", "./fonts/retganon.ttf", 16);
}

void Game::HandleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
    case SDL_QUIT:
        is_running_ = false;
        break;
    case SDL_KEYDOWN:
        current_map_->HandleInput(event);
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
    int tmp = SDL_GetTicks();
    if (tmp - timestamp_ >= skip_) {
        if (!current_map_->IsLegal()) // movement is illegal
            std::cout << "illegal" << std::endl;
        else
            current_map_->Move();
        timestamp_ = SDL_GetTicks();
    }
}

void Game::Render() {
    SDL_RenderClear(renderer_);
    // where we add stuff to render in rendering order {map -> chars -> menus}
    current_map_->DrawMap();

    player_->Render();

    FontManager::Instance()->Draw("retganon", "PLATAL GAME!", 250, 0,
                                  {200, 50, 50}, renderer_);

    SDL_RenderPresent(renderer_);
}