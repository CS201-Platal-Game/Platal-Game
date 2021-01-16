#include "character.h"
#include "game.h"
#include "platal_map.h"
#include "utils/texture_manager.h"
#include <string>
#include <vector>

Character::Character() {}

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
    hitbox_.x = position_.x;
    hitbox_.y = position_.y;
    return hitbox_;
}

/********* PROTAGONIST *********/
Protagonist::Protagonist() { // default constructor
    stats_ = Stats();
}

Protagonist::Protagonist(const std::string& name, const Position& position) {
    stats_ = Stats();
    viewport_center_ = position;
    position_ = {0, 0};
}

// constructor
Protagonist::Protagonist(const std::string& name, const Position& position,
                         std::vector<std::pair<std::string, std::string>> idfiles) {
    stats_ = Stats();
    viewport_center_ = position;
    position_ = {0, 0};

    // fills animation array w/ instances of animations
    std::vector<std::pair<std::string, std::string>>::iterator i;
    for (i = idfiles.begin(); i != idfiles.end(); ++i) {
        animationArray_.push_back(AnimatedTexture(i->first, 0, 6, 32, 32, viewport_center_.x, viewport_center_.y));
        TextureManager::Instance()->Load(i->first, i->second, Game::renderer_);
    }
}

void Protagonist::CreateAnimationArray(std::vector<std::pair<std::string, std::string>> idfiles) {
    // function to fill animation array
    std::vector<AnimatedTexture> textureArray;
    std::vector<std::pair<std::string, std::string>>::iterator i;
    for (i = idfiles.begin(); i != idfiles.end(); ++i) {
        TextureManager::Instance()->Load(i->first, i->second, Game::renderer_);
        textureArray.push_back(AnimatedTexture(i->first, 0, 5, 32, 32, viewport_center_.x, viewport_center_.y));
    }
    animationArray_ = textureArray;
}

void Protagonist::Render() {
    if (animationArray_.empty()) {
        TextureManager::Instance()->Draw("player", {0, 0, 32, 32},
                                         {viewport_center_.x, viewport_center_.y, 64, 64},
                                         Game::renderer_);
    } else {
        const Uint8* event_array = SDL_GetKeyboardState(nullptr);
        // array (by index): 0: left, 1: right, 2: up, 4: down
        switch (Map::protag_orientation_) {
        case kLeft: {
            if (event_array[SDL_SCANCODE_LEFT] && (Game::game_state_ == kWorld)) {
                // key pressed -> run through the frames
                animationArray_[0].Render(viewport_center_.x, viewport_center_.y, false);
                animationArray_[0].Update();
            } else {
                // shows first frame (static)
                animationArray_[0].Render(viewport_center_.x, viewport_center_.y, true);
            }
            break;
        }

        case kRight: {
            if (event_array[SDL_SCANCODE_RIGHT] && (Game::game_state_ == kWorld)) {
                animationArray_[1].Render(viewport_center_.x, viewport_center_.y, false);
                animationArray_[1].Update();
            } else {
                animationArray_[1].Render(viewport_center_.x, viewport_center_.y, true);
            }
            break;
        }

        case kUp: {
            if (event_array[SDL_SCANCODE_UP] && (Game::game_state_ == kWorld)) {
                animationArray_[2].Render(viewport_center_.x, viewport_center_.y, false);
                animationArray_[2].Update();
            } else {
                animationArray_[2].Render(viewport_center_.x, viewport_center_.y, true);
            }
            break;
        }

        case kDown: {
            if (event_array[SDL_SCANCODE_DOWN] && (Game::game_state_ == kWorld)) {
                animationArray_[3].Render(viewport_center_.x, viewport_center_.y, false);
                animationArray_[3].Update();
            } else {
                animationArray_[3].Render(viewport_center_.x, viewport_center_.y, true);
            }
            break;
        }

        default: // renders the static image
            TextureManager::Instance()->Draw(name_, {0, 0, 32, 32},
                                             {viewport_center_.x, viewport_center_.y, 64, 64}, Game::renderer_);
        }
    }
}

/********* NPC *********/
void NPC::MoveRoute() {
    if (moving_) {
        if (route_.empty()) {
            moving_ = false;
        } else {
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
