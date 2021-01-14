#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "utils/structs.h"
#include "utils/Animation.h"
#include "dialogue.h"
#include "stats.h"
#include <string>
#include <list>
#include <vector>
#include <map>

enum Direction {
    kLeft = 0,
    kRight, // 1
    kUp, // 2
    kDown, // 3
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
    SDL_Rect GetHitbox();

    virtual void Render();
    void Update(); //TODO: implement update method

  protected:
    std::string name_;
    int char_id;
    Position position_{ 0, 0 };
    SDL_Rect hitbox_;
    Direction orientation_; // e.g. protag is facing up/down/etc.
    int frames_ = 0;
    int speed_ = 100; //delay between frames, in milliseconds

};

class Protagonist : public Character {
  public:
    // inherit constructors
    Protagonist();
    Protagonist(const std::string& name, const Position& position);
    Protagonist(const std::string& name, const Position& position,
     std::vector<std::pair<std::string, std::string>> idfiles);
    //Takes key presses and adjusts the protag's orientation
    void HandleInput(SDL_Event key);

    // Assumed possible movement (checked by Map or Game).
    // We move depending on the state of the velocity 
    void Move();

    void Render();

    void CreateAnimationArray(std::vector<std::pair<std::string, std::string>> idfiles);

  private:
    std::vector<AnimatedTexture> animationArray_;
    Position viewport_center_;
    Stats stats_;
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
