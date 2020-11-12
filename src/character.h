#pragma once

#include "dialogue.h"
#include "stats.h"
#include <string>

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

    // Assumed possible movement (checked by Map or Game).
    // Ask Elouan for how x, y should be modified.
    void Move(Direction direction);

  protected:
    std::string name_;
    Position position_;
    // TODO: sprites
};

class Protagonist : public Character {
  public:
  private:
    Direction orientation_; // e.g. protag is facing up/down/etc.
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
