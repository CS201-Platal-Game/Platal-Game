#include "character.h"
#include "game.h"

void Protagonist::HandleInput() {
    // move left
    if(Game::event_array_[SDLK_LEFT]) {
        velocity_.xVel -= 1; // number here is subject to change depending on how the movement feels when testing
    }
    // move right
    if(Game::event_array_[SDLK_RIGHT]) {
        velocity_.xVel += 1;
    }
    //move up
    if(Game::event_array_[SDLK_UP]) { 
        velocity_.yVel += 1;
    }
    // move down
    if(Game::event_array_[SDLK_DOWN]) { 
        velocity_.yVel -= 1;
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
            velocity_.xVel += 5; // value subject to change
            // we now treat the case where we overshoot 0
            if( velocity_.xVel > 0){
                velocity_.xVel = 0;
            }
        }
    }
    
    if( !Game::event_array_[SDLK_RIGHT] ){
        if( velocity_.xVel > 0){
            velocity_.xVel -= 5;
            if( velocity_.xVel > 0){
                velocity_.xVel = 0;
            }
        }
    }

    if( !Game::event_array_[SDLK_UP] ){
        if( velocity_.yVel > 0){
            velocity_.yVel -= 5;
            if( velocity_.yVel > 0){
                velocity_.yVel = 0;
            }
        }
    }

    if( !Game::event_array_[SDLK_DOWN] ){
        if( velocity_.yVel < 0){
            velocity_.yVel += 5;
            if( velocity_.yVel > 0){
                velocity_.yVel = 0;
            }
        }
    }
}
