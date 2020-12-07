#pragma once
#include "dialogue.h"
#include "stats.h"
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

enum Direction {
    kLeft = 0,
    kRight,
    kUp,
    kDown
};

class Character {
  public:
    struct Position {
        int x, y;
    };

    Character();
    Character(const std::string& name, const Position& position);
    ~Character();

    std::string GetName();
    Position GetPosition();
    SDL_Rect rect_;
    void Render();
    void Update();

  protected:
    std::string name_;
    Position position_;
    Direction orientation_; // e.g. protag is facing up/down/etc.
    // TODO: sprites
};

class Protagonist : public Character {
  public:
    struct Velocity {
        int xVel, yVel;
    };

    //Takes key presses and adjusts the protag's velocity
    void HandleInput(SDL_Event key);

    // Assumed possible movement (checked by Map or Game).
    // We move depending on the state of the velocity 
    void Move();

  private:
    Velocity velocity_;
    Stats stats_;
    // TODO: inventories?
};

class NPC : public Character {
  public:
    void AddDialogue(Dialogue* const dialogue);

    // NPC follows a fixed route, or stand still if interrupted / empty route_.
    void MoveRoute();

    // Triggers conversations or actions.
    // Might return a status (enum/int) instead.
    void Interact();

  private:
    std::vector<Direction> route_;     // NPC fixed movements.
    std::vector<Dialogue*> dialogues_; // NPC possible dialogues.
};
