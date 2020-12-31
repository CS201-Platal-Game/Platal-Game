#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "platal_map.h"
#include <iostream>

class Game {
  public:
    // this stays just in the unlikely case that we wish to make game a singleton
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
              int width, int height,
              bool fullscreen);

    void HandleEvents(); // reacts to user input
    void Update();       // gets the objects to react to user input
    void Render();       // renders all elements to screen

    void ChangeMap(int map_id); // TODO think about how this is gonna be implemented - for later

    bool Running() { return is_running_; }

    static SDL_Renderer* renderer_;

    static bool is_in_dialogue;

  private:
    int width_, height_;
    bool is_running_;
    int count_ = 0;
    SDL_Window* window_;
    Map* current_map_;
    Protagonist* player_;
    Dialogue* current_dialogue;
    static Game* myInstance;
};
