#include "character.h"
#include "game.h"
#include "platal_map.h"
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
Protagonist::Protagonist() { // default constructor
  stats_ = Stats();
}

Protagonist::Protagonist(const std::string &name, const Position &position) {
  stats_ = Stats();
  viewport_center_ = position;
  position_ = {0,0};
}

// constructor - dunno if this is too messy, contact Nina if that's the case
Protagonist::Protagonist(const std::string &name, const Position &position,
 std::vector<std::pair<std::string, std::string>> idfiles) {
  stats_ = Stats();
  viewport_center_ = position;
  position_ = {0,0};

  // the following is my fancy scheme to fill the animation array w/ instances of animations
  std::vector<std::pair<std::string, std::string>>::iterator i;
  for (i = idfiles.begin(); i != idfiles.end(); ++i) {
        //below - id: , curr frame: 0, max frame (fixed): 6, width x height: 32 x 32, posX posY: viewport.x, viewport.y
        animationArray_.push_back(AnimatedTexture(i->first, 0, 6, 32, 32, viewport_center_.x, viewport_center_.y));
        TextureManager::Instance()->Load(i->first, i->second, Game::renderer_);
    } 
}

void Protagonist::CreateAnimationArray(std::vector<std::pair<std::string, std::string>> idfiles){
    // function to fill animation array
    // This is meant to create the array of instances of "AnimatedTexture" based on the input of the files to load
    // and the IDs.
    // THESE VECTORS NEED !!!! TO BE OF THE SAME LENGTH !!!!

    std::vector<AnimatedTexture> textureArray; // create an array with the number of files to load
    // fill the array w instances of AnimatedTexture
    std::vector<std::pair<std::string, std::string>>::iterator i;
    for (i = idfiles.begin(); i != idfiles.end(); ++i) {
        TextureManager::Instance()->Load(i->first, i->second, Game::renderer_);
        //below - id: , curr frame: 0, max frame (fixed): 6, width x height: 32 x 32, posX posY: viewport.x, viewport.y
        textureArray.push_back(AnimatedTexture(i->first, 0, 5, 32, 32, viewport_center_.x, viewport_center_.y));
    }

    animationArray_ = textureArray; // set attribute
}

void Protagonist::Render() { // DO ANIMATION STUFF HERE, use array, this should only be one line
    if (animationArray_.empty()){
        TextureManager::Instance()->Draw("player", {0, 0, 32, 32},
                                         {viewport_center_.x, viewport_center_.y, 64, 64},
                                         Game::renderer_);
    } else {
        // do only on protagonist
        const Uint8* event_array = SDL_GetKeyboardState(nullptr);
        // the array will work as follows (by index): 0: left, 1: right, 2: up, 4: down
        switch (Map::protag_orientation_) {
            case kLeft: {
                AnimatedTexture leftAnimate = animationArray_[0]; // creates this variable for clarity
                    leftAnimate.Render(viewport_center_.x, viewport_center_.y, false);
                    leftAnimate.Update(); // run through the frames
                }
                break;

            case kRight: {
                AnimatedTexture rightAnimate = animationArray_[1];
                /*if (event_array[SDL_SCANCODE_RIGHT]) {
                    rightAnimate.Render(viewport_center_.x, viewport_center_.y, false);
                    rightAnimate.Update();
                } else {
                    rightAnimate.Render(viewport_center_.x, viewport_center_.y, true);
                }*/
                rightAnimate.Render(viewport_center_.x, viewport_center_.y, false);
                rightAnimate.Update();
                }
                break;

            case kUp: {
                AnimatedTexture upAnimate = animationArray_[2];
                    upAnimate.Render(viewport_center_.x, viewport_center_.y, false);
                    upAnimate.Update();
                }
                break;

            case kDown: {
                AnimatedTexture downAnimate = animationArray_[3];
                    downAnimate.Render(viewport_center_.x, viewport_center_.y, false);
                    downAnimate.Update();
                }
                break;

            default: // default is to just render the static image
                // I can either do it like this or using the animation class
                // don't know - which is better?
                TextureManager::Instance()->Draw(name_, {0, 0, 32, 32},
                                                 {viewport_center_.x, viewport_center_.y, 64, 64}, Game::renderer_);
        }
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
