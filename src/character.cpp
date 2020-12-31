#include "character.h"
#include "game.h"
#include "utils/texture_manager.h"

Character::Character(){}

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


void Protagonist::Render() {
    TextureManager::Instance()->Draw(name_, {0, 0, 32, 32},
                                     {viewport_center_.x, viewport_center_.y, 64, 64}, Game::renderer_);
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
