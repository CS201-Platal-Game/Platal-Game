#pragma once
#include "HUD.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "clock.h"
#include "dialogue.h"
#include "menu.h"
#include "platal_map.h"
#include "quiz.h"
#include <iostream>

enum GameState { kWorld = 0,
                 kDialogue,
                 kSynapses,
                 kQuiz,
                 kMenu,
                 kQuit };

class Game {
  public:
    // this stays just in the unlikely case that we wish to make game a
    // singleton
    /*static Game* Instance(){
        if (myInstance == 0){
            myInstance = new Game();
        }
        return myInstance;
    }*/

    Game();
    ~Game();

    void Init(const char* title,
              int xpos, // x position where the window is initialized
              int ypos, // y position where the window is initialized
              int width, int height, bool fullscreen);

    void HandleEvents(); // reacts to user input
    void Update();       // gets the objects to react to user input
    void Render();       // renders all elements to screen

    bool Running() { return is_running_; }

    static SDL_Renderer* renderer_;
    static SDL_Window* window_;
    static GameState game_state_;
    static Map* current_map_;

  private:
    int width_, height_;
    bool is_running_;
    int count_ = 0;
    HUD* hud_;
    Protagonist* player_;
    Dialogue* current_dialogue_;
    Quiz* current_quiz_;
    MainMenu* main_menu_;
    Synapses* synapses_;
    Clock* clock_;
    static Game* myInstance;

    // to skip control input
    int skip_ = 40;
    int timestamp_ = SDL_GetTicks();
};
