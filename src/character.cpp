#include "character.h"
#include "game.h"
#include "utils/texture_manager.h"

Character::Character(){};

Character::Character(const std::string& name, const Position& position) {
    name_ = name;
    position_ = position;
    orientation_ = kDown;
}

Character::~Character() {}

std::string Character::GetName() {
    return name_;
}

Position Character::GetPosition() {
    return position_;
}

void Character::Render() {
    TextureManager::Instance()->drawFrame(name_,
                                          position_.x, position_.y,
                                          32, 32, //size
                                          1, 0, //row, frame
                                          Game::renderer_);
}


/********* PROTAGONIST *********/
Protagonist::Protagonist() {
  stats_ = Stats();
}

Protagonist::Protagonist(const std::string &name, const Position &position)
    : Character(name, position) {
  stats_ = Stats();
}


void Protagonist::HandleInput(SDL_Event event) {
    switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            orientation_ = kLeft;
            velocity_.yVel = 0;
            velocity_.xVel = 0;
            break;
        
        case SDLK_RIGHT:
            orientation_ = kRight;
            velocity_.yVel = 0;
            velocity_.xVel = 0;
            break;

        case SDLK_UP:
            orientation_ = kUp;
            velocity_.yVel = 0;
            velocity_.xVel = 0;
            break;

        case SDLK_DOWN:
            orientation_ = kDown;
            velocity_.yVel = 0;
            velocity_.xVel = 0;
            break;
        default:
            break;
    }
}

void Protagonist::Move() {
    // The orientation allows us to determine what the last pressed key is
    const Uint8* event_array = SDL_GetKeyboardState(NULL);
    switch (orientation_){
        case kLeft:
            // update the velocities so they increase if a key is being pressed or fall back to zero when a key isn't being pressed
            if( event_array[SDL_SCANCODE_LEFT] ) {
                if( velocity_.xVel > -64 ) { // We want to limit the velocity in any direction at 64
                    velocity_.xVel -= 8;
                    if( velocity_.xVel < -64 ) { // We check after increasing that we are not above the limit
                        velocity_.xVel = 64;
                    }
                }
            }
            else if( velocity_.xVel < 0){
                    velocity_.xVel += 16; // value subject to change
                    // we now treat the case where we overshoot 0
                    if( velocity_.xVel > 0){
                        velocity_.xVel = 0;
                    }
            }
            break;
        
        case kRight:
            if( event_array[SDL_SCANCODE_RIGHT] ) {
                if( velocity_.xVel < 64 ) { 
                    velocity_.xVel += 8;
                    if( velocity_.xVel > 64 ) { 
                        velocity_.xVel = 64;
                    }
                }
            }
            else if( velocity_.xVel > 0){
                    velocity_.xVel -= 16; 
                    if( velocity_.xVel < 0){
                        velocity_.xVel = 0;
                    }
            }
            break;
        
        case kUp:
            if( event_array[SDL_SCANCODE_UP] ) {
                if( velocity_.yVel < 64 ) { 
                    velocity_.yVel += 8;
                    if( velocity_.yVel > 64 ) { 
                        velocity_.yVel = 64;
                    }
                }
            }
            else if( velocity_.yVel > 0){
                    velocity_.yVel -= 16; 
                    if( velocity_.yVel < 0){
                        velocity_.yVel = 0;
                    }
            }
            break;

        case kDown:
            if( event_array[SDL_SCANCODE_DOWN] ) {
                if( velocity_.yVel > -64 ) { 
                    velocity_.yVel -= 8;
                    if( velocity_.yVel < -64 ) { 
                        velocity_.yVel = 64;
                    }
                }
            }
            else if( velocity_.yVel < 0){
                    velocity_.yVel += 16; 
                    if( velocity_.yVel > 0){
                        velocity_.yVel = 0;
                    }
            }
            break;
        
        default:
            break;
    }

    //Move the protag left or right
    position_.x += velocity_.xVel;
    
    //Move the protag up or down
    position_.y += velocity_.yVel;
}
