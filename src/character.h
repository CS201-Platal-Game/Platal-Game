#pragma once
#include "dialogue.h"
#include "stats.h"
#include "utils/structs.h"
#include "utils/Animation.h"
#include <string>
#include <list>
#include <vector>

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
    SDL_Rect GetHitbox();

    virtual void Render();
    void Update(); 

  protected:
    std::string name_;
    int char_id;
    Position position_{ 0, 0 };
    SDL_Rect hitbox_;
    Direction orientation_; // facing up/down/etc.
};

class Protagonist : public Character {
  public:
    Protagonist();
    // files and ids are for animation purposes
    Protagonist(const std::string &name, const Position &position);
    Protagonist(const std::string &name, const Position &position,
 std::vector<std::pair<std::string, std::string>> idfiles);

    void Render();
    void CreateAnimationArray(std::vector<std::pair<std::string, std::string>> idfiles);

  private:
    Position viewport_center_;
    Stats stats_;
    std::vector<AnimatedTexture> animationArray_;
};

class NPC : public Character {
  public:
    // inherit constructors
    using Character::Character;

    void AddDialogue(Dialogue* const dialogue);

    void MoveRoute(); // NPC follows a fixed route, or stands still if interrupted / empty route_.

  private:
    bool moving_ = false;
    std::list<Direction> route_;     // NPC fixed movements
    std::vector<Dialogue*> dialogues_; // NPC possible dialogues.
};
