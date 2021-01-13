#include "character.h"
#include "game.h"
#include "utils/texture_manager.h"
#include <vector>
#include <string>

Character::Character(){}

Character::Character(const std::string& name, const Position& position) {
    name_ = name;
    position_ = position;
    orientation_ = kDown;
    hitbox_.h = 32;
    hitbox_.w = 32;
    hitbox_.x = position.x;
    hitbox_.y = position.y;
}

Character::~Character() {}

std::string Character::GetName() {
    return name_;
}

Position Character::GetPosition() {
    return position_;
}

Position* Character::GetPositionPointer() {
    return &position_;
}

void Character::Render() {
    TextureManager::Instance()->Draw(name_, {0, 0, 32, 32},
                                     {position_.x, position_.y, 64, 64}, Game::renderer_);
}

int Character::GetCharId() {
    return char_id;
}

SDL_Rect Character::GetHitbox() {
    // Update the hitbox x and y before returning it
    hitbox_.x = position_.x;
    hitbox_.y = position_.y;
    return hitbox_;
}

/********* PROTAGONIST *********/
Protagonist::Protagonist() {
  stats_ = Stats();
}

Protagonist::Protagonist(const std::string &name, const Position &position)
    : Character(name, position) {
  stats_ = Stats();
  viewport_center_ = position;
  position_ = {0,0};
}


void Protagonist::HandleInput(SDL_Event event) {
    switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            orientation_ = kLeft;
            velocity_.yVel = 0;
            //velocity_.xVel = 0;
            break;
        
        case SDLK_RIGHT:
            orientation_ = kRight;
            velocity_.yVel = 0;
            //velocity_.xVel = 0;
            break;

        case SDLK_UP:
            orientation_ = kUp;
            //velocity_.yVel = 0;
            velocity_.xVel = 0;
            break;

        case SDLK_DOWN:
            orientation_ = kDown;
            //velocity_.yVel = 0;
            velocity_.xVel = 0;
            break;
        default:
            break;
    }
}

void Protagonist::Move() {
    // The orientation allows us to determine what the last pressed key is
    const Uint8* event_array = SDL_GetKeyboardState(nullptr);
    switch (orientation_){
        case kLeft:
            // update the velocities so they increase if a key is being pressed or fall back to zero when a key isn't being pressed
            if( event_array[SDL_SCANCODE_LEFT] ) {
                if( velocity_.xVel > -accel_.terminalVelocity ) { // We want to limit the velocity in any direction; originally at 64
                    velocity_.xVel -= accel_.speedUp;
                    if( velocity_.xVel < -accel_.terminalVelocity ) { // We check after increasing that we are not above the limit
                        velocity_.xVel = accel_.terminalVelocity;
                    }
                }
            }
            else if( velocity_.xVel < 0){
                    velocity_.xVel += accel_.sloDown; // value subject to change
                    // we now treat the case where we overshoot 0
                    if( velocity_.xVel > 0){
                        velocity_.xVel = 0;
                    }
            }
            break;
        
        case kRight:
            if( event_array[SDL_SCANCODE_RIGHT] ) {
                if( velocity_.xVel < accel_.terminalVelocity ) {
                    velocity_.xVel += accel_.speedUp;
                    if( velocity_.xVel > accel_.terminalVelocity ) {
                        velocity_.xVel = accel_.terminalVelocity;
                    }
                }
            }
            else if( velocity_.xVel > 0){
                    velocity_.xVel -= accel_.sloDown;
                    if( velocity_.xVel < 0){
                        velocity_.xVel = 0;
                    }
            }
            break;
        
        case kDown:
            if( event_array[SDL_SCANCODE_DOWN] ) {
                if( velocity_.yVel < accel_.terminalVelocity ) {
                    velocity_.yVel += accel_.speedUp;
                    if( velocity_.yVel > accel_.terminalVelocity ) {
                        velocity_.yVel = accel_.terminalVelocity;
                    }
                }
            }
            else if( velocity_.yVel > 0){
                    velocity_.yVel -= accel_.sloDown;
                    if( velocity_.yVel < 0){
                        velocity_.yVel = 0;
                    }
            }
            break;

        case kUp:
            if( event_array[SDL_SCANCODE_UP] ) {
                if( velocity_.yVel > -accel_.terminalVelocity ) {
                    velocity_.yVel -= accel_.speedUp;
                    if( velocity_.yVel < -accel_.terminalVelocity ) {
                        velocity_.yVel = accel_.terminalVelocity;
                    }
                }
            }
            else if( velocity_.yVel < 0){
                velocity_.yVel += accel_.sloDown;
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

void Protagonist::Render() { // DO ANIMATION STUFF HERE, use array, this should only be one line
    // do only on protagonist
    TextureManager::Instance()->Draw(name_, {0, 0, 32, 32},
                                     {viewport_center_.x, viewport_center_.y, 64, 64}, Game::renderer_);
}

// test test
void Protagonist::CreateAnimationArray(vector<string> files, vector<string> ids){
    // This is meant to create the array of instances of "AnimatedTexture" based on the input of the files to load
    // and the IDs.
    // THESE VECTORS NEED !!!! TO BE OF THE SAME LENGTH !!!!

    int length = files.size(); // gives number of elements in map, i.e. nr of files to load
    AnimatedTexture textureArray[length] // create an array with the number of files to load

    // fill the array w instances of AnimatedTexture
    for (i = ids.begin(); i != ids.end(); ++i) {
        //below - id: , curr frame: 0, max frame (fixed): 6, width x height: 32 x 32, posX posY: viewport.x, viewport.y
        textureArray[i] = AnimatedTexture(ids[i], 0, 6, 32, 32, viewport.x, viewport.y);
    }
    
    // load the image files into the texture map
    for (i = files.begin(); i != files.end(); ++i){
        TextureManager::Instance()->Load(ids[i], files[i], Game::renderer_);
    }
}


/********* NPC *********/

void NPC::MoveRoute() {
    if (moving_ ) {
        if (route_.empty()) {
            moving_ = false;
        }
        else {
            Direction direction = route_.back();
            route_.pop_back();
            
            switch (direction) {
                case kLeft:
                    position_.x -= 8;
                    break;

                case kRight:
                    position_.x += 8;
                    break;
                
                case kUp:
                    position_.y -= 8;
                    break;
                
                case kDown:
                    position_.y += 8;
                    break;
                
                case stop:
                    moving_ = false;
                    break;
                
                default:
                    break;
            }
        }
    }
}
