#include "character.h"
#include "game.h"

Character::Character(const std::string& name, const Position& position) {
    name_ = name;
    position_ = position;
    orientation_ = kDown;
}

std::string Character::GetName() {
    return name_;
}

Character::Position Character::GetPosition() {
    return position_;
}

void Protagonist::HandleInput(SDL_Event event) {
    switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            orientation_ = kLeft;
            velocity_.yVel = 0;
            if(velocity_.xVel>0) velocity_.xVel = 0;
            velocity_.xVel -= 8;
            break;
        
        case SDLK_RIGHT:
            orientation_ = kRight;
            velocity_.yVel = 0;
            if(velocity_.xVel<0) velocity_.xVel = 0;
            velocity_.xVel += 8;
            break;

        case SDLK_UP:
            orientation_ = kUp;
            velocity_.xVel = 0;
            if(velocity_.yVel<0) velocity_.yVel = 0;
            velocity_.yVel += 8;
            break;

        case SDLK_DOWN:
            orientation_ = kDown;
            velocity_.xVel = 0;
            if(velocity_.yVel>0) velocity_.yVel = 0;
            velocity_.yVel -= 8;
            break;
    }
}

void Protagonist::Move() {
    //Move the protag left or right
    position_.x += velocity_.xVel;
    
    //Move the protag up or down
    position_.y += velocity_.yVel;

    // update the velocities so they fall back to zero when a key isn't being pressed
    if( !Game::event_array_[SDLK_LEFT] ){
        if( velocity_.xVel < 0){
            velocity_.xVel += 16; // value subject to change
            // we now treat the case where we overshoot 0
            if( velocity_.xVel > 0){
                velocity_.xVel = 0;
            }
        }
    }
    
    if( !Game::event_array_[SDLK_RIGHT] ){
        if( velocity_.xVel > 0){
            velocity_.xVel -= 16;
            if( velocity_.xVel > 0){
                velocity_.xVel = 0;
            }
        }
    }

    if( !Game::event_array_[SDLK_UP] ){
        if( velocity_.yVel > 0){
            velocity_.yVel -= 16;
            if( velocity_.yVel > 0){
                velocity_.yVel = 0;
            }
        }
    }

    if( !Game::event_array_[SDLK_DOWN] ){
        if( velocity_.yVel < 0){
            velocity_.yVel += 16;
            if( velocity_.yVel > 0){
                velocity_.yVel = 0;
            }
        }
    }
}
