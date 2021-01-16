#pragma once
#include "character.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "utils/structs.h"
#include <string>

class Object {
  public:
    
    Object();
    Object(int width, int height, bool collidable);
    Object(std::string texture_id, int width, int height, bool collidable, int x, int y);
    ~Object();
    // may want to have a texture sheet as an argument in the constructor,
    // to do once we have a functioning texture manager

    int GetWidth();
    int GetHeight();
    int GetObjId();
    bool IsCollidable();
    Position GetPosition();
    SDL_Rect GetHitbox();
    void SetHitbox(int width, int height);

    // Returns a copy of the object.
    Object Copy();

    // Allows the player to interact with the object
    void Action1();
    void Action2();

    // Check if the player is colliding with the object
    bool CheckCollision(Character character);
    bool CheckCollision(SDL_Rect hitbox);
    template <typename T> void CollideInterract(T item){
      if (CheckCollision(item)) {
        Action1();
      }
    }

    // A method that calls an interaction if a sufficient condition is met
    // To be defined in the subclasses
    void Interact();

    void Render();

  protected:
    std::string textureId_; // string to link to texture map
    SDL_Rect hitbox_;
    bool collidable_;
    Position position_; // the up-left position of the object
    int obj_id;

};

// Object signalling map changes.
class Portal : public Object {
  public:
    Portal(SDL_Rect coordinates, std::string map_id, Position starting_position);
    bool CheckCollision(SDL_Rect hitbox);
    void Action1();

  private:
    std::string map_id_;
    Position starting_position_;
};

class Switch : public Object {
  public:
    using Object::Object;
    Switch(int width, int height, bool collidable, int x, int y,
    int offset, int interact_width, int interact_height, bool state);
    SDL_Rect GetField();
    void SetField(int offset, int width, int height);
    void KeyInteraction(Character character);
    void KeyInteraction(SDL_Rect hitbox);
    void ToggleState();
    void SetState(bool state);
    bool GetState();

  private:
    SDL_Rect interact_field_;
    bool active_ = true;
    bool state_;
};