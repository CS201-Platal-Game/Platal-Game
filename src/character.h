#pragma once
#include "dialogue.h"
#include "stats.h"
#include "utils/structs.h"
#include <string>
#include <list>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

enum Direction {
    kLeft = 0,
    kRight,
    kUp,
    kDown,
    stop
};

class Character {
  public:
    Character();
    Character(const std::string& name, const Position& position);
    ~Character();
    int GetCharId();
    std::string GetName();
    Position GetPosition();
    Position* GetPositionPointer();
    SDL_Rect rect_;
    void Render();
    void Update();

  protected:
    std::string name_;
    int char_id;
    Position position_{ 0, 0 };
    Direction orientation_; // e.g. protag is facing up/down/etc.
    // TODO: sprites
};

class Protagonist : public Character {
  public:
    struct Velocity {
        int xVel, yVel;
    };
    struct Accel {
        int terminalVelocity, speedUp, sloDown;
    };

    // inherit constructors
    Protagonist();
    Protagonist(const std::string& name, const Position& position);

    //Takes key presses and adjusts the protag's orientation
    void HandleInput(SDL_Event key);

    // Assumed possible movement (checked by Map or Game).
    // We move depending on the state of the velocity 
    void Move();

  private:
    Velocity velocity_{ 0, 0 };
    Stats stats_;
    Accel accel_ = {32, 4, 8};
    // TODO: inventories?
};

class NPC : public Character {
  public:
    // inherit constructors
    using Character::Character;

    void AddDialogue(Dialogue* const dialogue);

    // NPC follows a fixed route, or stand still if interrupted / empty route_.
    // Only functions if moving_ is true, pops last element from route_ and goes in that direction
    void MoveRoute();

    // Triggers conversations or actions.
    // Might return a status (enum/int) instead.
    void Interact();

  private:
    bool moving_ = false;
    std::list<Direction> route_;     // NPC fixed movements, the next move is located at the back, to add a new move just push to the front.
    std::vector<Dialogue*> dialogues_; // NPC possible dialogues.
};
