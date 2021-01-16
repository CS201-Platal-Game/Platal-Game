#include "platal_map.h"
#include "game.h" // added game.h, just in case
#include "utils/csv2map.h"
#include "utils/sound_manager.h"

Direction Map::protag_orientation_ = kDown;

Map::Map() {
    TextureManager::Instance()->Load("dirt", "./images/maptexture/dirt.png", Game::renderer_);
    TextureManager::Instance()->Load("water", "./images/maptexture/water.png", Game::renderer_);
    TextureManager::Instance()->Load("grass_1l", "./images/maptexture/grasstile_oneleaf.png", Game::renderer_);

    src_ = dest_ = {0, 0, 64, 64};

    // width and height of the map in squares
    width_ = height_ = 0;

    // get the viewport dimensions
    SDL_GetWindowSize(Game::window_, &vpwidth_, &vpheight_);
    std::cout << vpwidth_ << ", " << vpheight_ << std::endl
              << std::endl;
}

void Map::LoadMap(char* filename, Position starting_pos) {
    struct MapBundle tmp;
    tmp = csv2map(filename);
    width_ = tmp.width;
    height_ = tmp.height;
    map_array_ = tmp.map_array;
    music_ = tmp.music;

    // We now load and play the music
    if (music_ != "None") {
        std::string music_file = "./sound/music/";
        music_file.append(music_).append(".wav");
        SoundManager::Instance()->LoadMusic(music_, music_file);
        SoundManager::Instance()->PlayMusic(music_);
    }

    center_position_ = {starting_pos.x * 64 - vpwidth_ / 2,
                        starting_pos.y * 64 - vpheight_ / 2};
}

void Map::DrawMap() {

    int type = 0;

    std::string name;
    for (int width = 0; width < width_; width += 1) {
        for (int height = 0; height < height_; height += 1) {
            type = map_array_[height][width];
            switch (type) {
            case 1:
                name = "dirt";
                break;
            case 2:
                name = "grass_1l";
                break;
            case 3:
                name = "water";
                break;
            default:
                name = "";
                break;
            }
            if (name != "")
                TextureManager::Instance()->Draw(name, src_,
                                                 {64 * width - center_position_.x, 64 * height - center_position_.y, src_.w, src_.h},
                                                 Game::renderer_);
        }
    }
}

bool Map::IsLegal() {
    int x, y;
    switch (protag_orientation_) {
    case kLeft:
        x = (-1 + center_position_.x + vpwidth_ / 2 + protag_velocity_.xVel) / 64;
        y = (center_position_.y + vpheight_ / 2) / 64;
        break;
    case kRight:
        x = (1 + center_position_.x + vpwidth_ / 2 + protag_velocity_.xVel + 63) / 64;
        y = (center_position_.y + vpheight_ / 2) / 64;
        break;
    case kUp:
        x = (center_position_.x + vpwidth_ / 2) / 64;
        y = (-1 + center_position_.y + vpheight_ / 2 + protag_velocity_.yVel) / 64;
        break;
    case kDown:
        x = (center_position_.x + vpwidth_ / 2) / 64;
        y = (1 + center_position_.y + vpheight_ / 2 + protag_velocity_.yVel + 63) / 64;
        break;
    default:
        x = center_position_.x;
        y = center_position_.y;
        break;
    }
    return (x >= 0 and y >= 0 and x < width_ and y < height_ and map_array_[y][x] != 0);
}

void Map::HandleInput(SDL_Event event) {
    switch (event.key.keysym.sym) {
    case SDLK_LEFT:
        protag_orientation_ = kLeft;
        protag_velocity_.yVel = 0;
        break;

    case SDLK_RIGHT:
        protag_orientation_ = kRight;
        protag_velocity_.yVel = 0;
        break;

    case SDLK_UP:
        protag_orientation_ = kUp;
        protag_velocity_.xVel = 0;
        break;

    case SDLK_DOWN:
        protag_orientation_ = kDown;
        protag_velocity_.xVel = 0;
        break;

    case SDLK_e: {
        SDL_Rect new_hitbox_ = {center_position_.x, center_position_.y, 32, 32};
        std::vector<SDL_Rect> tiles_to_check = GetTiles(new_hitbox_);

        std::vector<SDL_Rect>::iterator iter;
        for (iter = tiles_to_check.begin(); iter != tiles_to_check.end(); iter++) {
            SDL_Rect rect = *iter;
            std::vector<Switch> vec_switch = switches_[rect];

            std::vector<Switch>::iterator vec_it;
            for (vec_it = vec_switch.begin(); vec_it != vec_switch.end(); vec_it++) {
                vec_it->KeyInteraction(new_hitbox_);
            }
        }
    } break;

    default:
        break;
    }
}

void Map::Move() {
    // The orientation allows us to determine what the last pressed key is
    const Uint8* event_array = SDL_GetKeyboardState(nullptr);
    switch (protag_orientation_) {
    case kLeft:
        // update the velocities so they increase if a key is being pressed or fall back to zero when a key isn't being pressed
        if (event_array[SDL_SCANCODE_LEFT]) {
            if (protag_velocity_.xVel > -protag_accel_.terminalVelocity) {
                protag_velocity_.xVel -= protag_accel_.speedUp;
                if (protag_velocity_.xVel < -protag_accel_.terminalVelocity) { // We check after increasing that we are not above the limit
                    protag_velocity_.xVel = protag_accel_.terminalVelocity;
                }
            }
        } else if (protag_velocity_.xVel < 0) {
            protag_velocity_.xVel += protag_accel_.sloDown;
            // we now treat the case where we overshoot 0
            if (protag_velocity_.xVel > 0) {
                protag_velocity_.xVel = 0;
            }
        }
        break;

    case kRight:
        if (event_array[SDL_SCANCODE_RIGHT]) {
            if (protag_velocity_.xVel < protag_accel_.terminalVelocity) {
                protag_velocity_.xVel += protag_accel_.speedUp;
                if (protag_velocity_.xVel > protag_accel_.terminalVelocity) {
                    protag_velocity_.xVel = protag_accel_.terminalVelocity;
                }
            }
        } else if (protag_velocity_.xVel > 0) {
            protag_velocity_.xVel -= protag_accel_.sloDown;
            if (protag_velocity_.xVel < 0) {
                protag_velocity_.xVel = 0;
            }
        }
        break;

    case kDown:
        if (event_array[SDL_SCANCODE_DOWN]) {
            if (protag_velocity_.yVel < protag_accel_.terminalVelocity) {
                protag_velocity_.yVel += protag_accel_.speedUp;
                if (protag_velocity_.yVel > protag_accel_.terminalVelocity) {
                    protag_velocity_.yVel = protag_accel_.terminalVelocity;
                }
            }
        } else if (protag_velocity_.yVel > 0) {
            protag_velocity_.yVel -= protag_accel_.sloDown;
            if (protag_velocity_.yVel < 0) {
                protag_velocity_.yVel = 0;
            }
        }
        break;

    case kUp:
        if (event_array[SDL_SCANCODE_UP]) {
            if (protag_velocity_.yVel > -protag_accel_.terminalVelocity) {
                protag_velocity_.yVel -= protag_accel_.speedUp;
                if (protag_velocity_.yVel < -protag_accel_.terminalVelocity) {
                    protag_velocity_.yVel = protag_accel_.terminalVelocity;
                }
            }
        } else if (protag_velocity_.yVel < 0) {
            protag_velocity_.yVel += protag_accel_.sloDown;
            if (protag_velocity_.yVel > 0) {
                protag_velocity_.yVel = 0;
            }
        }
        break;

    default:
        break;
    }

    //Move the protag left or right
    center_position_.x += protag_velocity_.xVel;

    //Move the protag up or down
    center_position_.y += protag_velocity_.yVel;

    SDL_Rect new_hitbox_ = {center_position_.x, center_position_.y, 32, 32};
    std::vector<SDL_Rect> tiles_to_check = GetTiles(new_hitbox_);

    std::vector<SDL_Rect>::iterator it;
    for (it = tiles_to_check.begin(); it != tiles_to_check.end(); it++) {
        SDL_Rect rect = *it;
        std::vector<Object> vec_obj = objects_[rect];

        std::vector<Object>::iterator vec_it;
        for (vec_it = vec_obj.begin(); vec_it != vec_obj.end(); vec_it++) {
            if (vec_it->IsCollidable()) {
                SDL_Rect obj_hitbox_ = vec_it->GetHitbox();
                if (SDL_HasIntersection(&obj_hitbox_, &new_hitbox_)) {
                    center_position_.x -= protag_velocity_.xVel;
                    center_position_.y -= protag_velocity_.yVel;
                    return;
                }
            }
        }
    }
}

void Map::AddObject(Object item) {
    std::vector<SDL_Rect> tiles = GetTiles(item);
    std::vector<SDL_Rect>::iterator it;
    for (it = tiles.begin(); it != tiles.end(); it++) {
        if (objects_.find(*it) == objects_.end()) {
            std::vector<Object>* list = new std::vector<Object>;
            objects_[*it] = *list;
        }
        objects_[*it].push_back(item);
    }
}

Object Map::RemoveObject(int obj_id) { // or maybe its name
    std::map<SDL_Rect, std::vector<Object>>::iterator map_it;
    Object res = Object();
    for (map_it = objects_.begin(); map_it != objects_.end(); map_it++) {
        std::vector<Object>::iterator vec_it;
        for (vec_it = map_it->second.begin(); vec_it != map_it->second.end(); vec_it++) {
            if (vec_it->GetObjId() == obj_id) {
                res = *vec_it;
                map_it->second.erase(vec_it);
            }
        }
    }
    return res;
}

Switch Map::RemoveSwitch(int obj_id) {
    std::map<SDL_Rect, std::vector<Switch>>::iterator map_it;
    Switch res = Switch();
    for (map_it = switches_.begin(); map_it != switches_.end(); map_it++) {
        std::vector<Switch>::iterator vec_it;
        for (vec_it = map_it->second.begin(); vec_it != map_it->second.end(); vec_it++) {
            if (vec_it->GetObjId() == obj_id) {
                res = *vec_it;
                map_it->second.erase(vec_it);
            }
        }
    }
    return res;
}

void Map::AddSwitch(Switch item) {
    std::vector<SDL_Rect> tiles = GetTiles(item);
    std::vector<SDL_Rect>::iterator it;
    for (it = tiles.begin(); it != tiles.end(); it++) {
        if (switches_.find(*it) == switches_.end()) {
            std::vector<Switch>* list = new std::vector<Switch>;
            switches_[*it] = *list;
        }
        switches_[*it].push_back(item);
    }
}

void Map::AddNpc(Character npc) {
    npc_[npc.GetPositionPointer()] = npc;
}

Character Map::RemoveNpc(int char_id) {
    for (std::map<Position*, Character>::iterator i = npc_.begin(); i != npc_.end(); i++) {
        if ((i->second).GetCharId() == char_id) {
            Character res = i->second;
            npc_.erase(i);
            return res;
        }
    }
    return Character();
}
