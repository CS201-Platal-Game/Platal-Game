#include "game.h"
#include "SDL2/SDL_ttf.h"
#include "platal_map.h"
#include "utils/font_manager.h"
#include "utils/sound_manager.h"
#include "utils/texture_manager.h"

// static members definition
SDL_Renderer* Game::renderer_ = nullptr;
SDL_Window* Game::window_ = nullptr;
Map* Game::current_map_ = nullptr;

// this stays just in the unlikely case that we wish to make game a singleton
// Game* Game::myInstance = 0;

GameState Game::game_state_ = GameState::kWorld;

Game::Game() { is_running_ = false; }

Game::~Game() {
    TextureManager::Instance()->Clean();
    std::cout << "cleaned textures" << std::endl;
    FontManager::Instance()->Clean();
    std::cout << "cleaned fonts" << std::endl;
    SoundManager::Instance()->Clean();
    std::cout << "cleaned sounds" << std::endl;

    delete hud_;
    delete current_dialogue_;
    delete clock_;
    delete synapses_;
    delete main_menu_;
    delete current_map_;

    SDL_DestroyRenderer(renderer_);
    std::cout << "freed renderer" << std::endl;
    SDL_DestroyWindow(window_);
    std::cout << "freed window" << std::endl;

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
        IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG && TTF_Init() == 0 &&
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == 0) {
        std::cout << "subsystem initialized..." << std::endl;

        window_ = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window_)
            std::cout << "window created..." << std::endl;

        renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
        if (renderer_) {
            SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0);
            std::cout << "renderer created..." << std::endl;
        }

        is_running_ = true;

        current_map_ = new Map();
        current_map_->LoadMap("./maps/room.csv", {6, 8});

        // create the game character
        player_ = new Protagonist("player", {width / 2, height / 2},
                                  std::vector<std::pair<std::string, std::string>>{
                                      {"play_left", "./images/sprites/man_walk_left.png"},
                                      {"play_right", "./images/sprites/man_walk_right.png"},
                                      {"play_up", "./images/sprites/man_walk_up.png"},
                                      {"play_down", "./images/sprites/man_walk_front.png"}});
        TextureManager::Instance()->Load(
            "player", "./images/sprites/neutral_forward.png", renderer_);

        FontManager::Instance()->Load("retganon10", "./fonts/chary___.ttf", 10);
        FontManager::Instance()->Load("retganon", "./fonts/chary___.ttf", 32);
	FontManager::Instance()->Load("fps", "./fonts/8bitlim.ttf", 18);

        SoundManager::Instance()->SetVolume(MIX_MAX_VOLUME / 2);

        // main menu
        main_menu_ = new MainMenu();

        // event manager
        synapses_ = new Synapses();
        clock_ = new Clock();
        synapses_->clock_ = clock_;
        clock_->synapses_ = synapses_;

        // create dialogue
        current_dialogue_ = new Dialogue("./dialogues/test.txt");

        // create hud
        hud_ = new HUD(2.5f, 50.0f, 50.0f);

    } else {
        std::cout << "SDL_ERROR: \t" << SDL_GetError() << std::endl;
        is_running_ = false;
    }
}

void Game::HandleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
    case SDL_QUIT:
        is_running_ = false;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE: {
            if (game_state_ == kWorld) {
                game_state_ = kMenu;
            }
            break;
        }
        default:
            break;
        }
        switch (game_state_) {
        case kWorld:
            current_map_->HandleInput(event);
            break;
        case kDialogue:
            current_dialogue_->HandleInput(event);
            break;
        case kQuiz:
            current_quiz_->HandleInput(event);
            break;
        case kMenu:
            main_menu_->HandleInput(event);
            break;
        case kSynapses:
            synapses_->HandleInput(event);
            break;
        default:
            break;
        }
        break;
    default:
        // to be extended once the facilities to handle user input have been
        // created
        break;
    }
}

void Game::Update() {
    switch (game_state_) {
    case kWorld: {
        int tick = SDL_GetTicks();
        if (tick - timestamp_ >= skip_) {
            if (!current_map_->IsLegal()) { // movement is illegal
                current_map_->ZeroSpeed();
            } else {
                current_map_->Move();
            }
            timestamp_ = SDL_GetTicks();
        }
        break;
    }
    case kQuit:
        is_running_ = false;
        break;
    default:
        break;
    }
}

void Game::Render() {
    SDL_RenderClear(renderer_);
    // where we add stuff to render in rendering order {map -> chars -> menus}
    current_map_->DrawMap();

    player_->Render();

    hud_->Render();

    // optional elements
    if (game_state_ == kDialogue) {
        current_dialogue_->Render();
    } else if (game_state_ == kMenu) {
        main_menu_->Render();
    } else if (game_state_ == kSynapses) {
        synapses_->Render();
    }

    //SDL_RenderPresent(renderer_);
    //SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0);
}


void Game::Show() { 
  SDL_RenderPresent(renderer_); 
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0); 
}

void Game::DisplayFps(int fps){
  FontManager::Instance()->Draw("fps", std::to_string(fps), 
				10, 10, {200, 200, 0, 200}, renderer_);
}
