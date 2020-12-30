#include "platal_map.h"
#include "game.h" // added game.h, just in case
#include "utils/csv2map.h"
//Chris here changing stuff for the map part, changes still need to be made, 



Map::Map() {
    // The textures we have for the moment are in Platal-Game -> images ->

    //Here we will add as many textures as needed, need yet to be determined
    TextureManager::Instance()->load("dirt", "./images/maptexture/dirt.png", Game::renderer_);
    TextureManager::Instance()->load("water", "./images/maptexture/water.png", Game::renderer_);
    TextureManager::Instance()->load("grass_1l", "./images/maptexture/grasstile_oneleaf.png", Game::renderer_);

    // sdl source and dest rects
    src_ = dest_ = {0, 0, 64, 64};

    // width and height of the map in squares
    width_ = height_ = 0;

    // get the viewport dimensions
    SDL_GetWindowSize(Game::window_, &vpwidth_, &vpheight_);
    std::cout << vpwidth_ << ", " << vpheight_ << std::endl << std::endl;
}
// The void Map::LoadMap I think has already been coded by Carolina, if not I'll do it


// Nina has completely forgotten how to use the texture manager pls help
// grasstile_oneleaf_ = TextureManager::load("grass1", "grasstile_oneleaf.png", Game::renderer_); //load the element so we are able to reference it later
void Map::LoadMap(char *filename, Position starting_pos) {
    struct MapBundle tmp;
    tmp = csv2map(filename);

    width_ = tmp.width;
    height_ = tmp.height;
    map_array_ = tmp.map_array;

    center_position_ = {starting_pos.x*64 - vpwidth_/2,
                        starting_pos.y*64 - vpheight_/2};
}


void Map::DrawMap() {

    int type = 0;

    std::string name;
    for(int width = 0; width < width_ ; width +=1){
        for(int height=0; height <height_ ; height +=1){
            type = map_array_[height][width];
            switch(type) {
                case 1: name = "dirt" ; break;
                case 2: name = "grass_1l"; break;
                case 3: name = "water"; break;
                default: name = ""; break;
            }
            if(name != "") 
                TextureManager::Instance()->Draw(name,src_ ,
                                                 {64*width - center_position_.x, 64*height - center_position_.y, src_.w, src_.h},
                                                 Game::renderer_);
            // Here I use TextureManager from texture_manager.cpp
        }
    }
}

/*
bool Map::IsLegal(Position pos, Velocity vel) {
    int vpwidth, vpheight;
    SDL_GetWindowSize(Game::window_, &vpwidth, &vpheight);
    vpwidth /= (2 * 64);
    vpheight /= (2 * 64);

    int x, y;
    x = (pos.x)/64 + vpwidth;
    y = (pos.y)/64 + vpheight;
    std::cout << y << ", " << x << ", " << map_array_[y][x] << std::endl;

    if (map_array_[y][x] != 0)
        return true;
    return false;
}*/

bool Map::IsLegal(){
    int x, y;
    x = (center_position_.x + vpwidth_/2 + protag_velocity_.xVel)/64;
    y = (center_position_.y + vpheight_/2 + protag_velocity_.yVel)/64;
    std::cout << x << ", " << y << "; " ;
    std::cout << map_array_[y][x] << std::endl;
    return (x >= 0 and y >= 0 and x < width_ and y < height_ and map_array_[y][x] != 0);
}

void Map::HandleInput(SDL_Event event) {
    switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            protag_orientation_ = kLeft;
            protag_velocity_.yVel = 0;
            //velocity_.xVel = 0;
            break;

        case SDLK_RIGHT:
            protag_orientation_ = kRight;
            protag_velocity_.yVel = 0;
            //velocity_.xVel = 0;
            break;

        case SDLK_UP:
            protag_orientation_ = kUp;
            //velocity_.yVel = 0;
            protag_velocity_.xVel = 0;
            break;

        case SDLK_DOWN:
            protag_orientation_ = kDown;
            //velocity_.yVel = 0;
            protag_velocity_.xVel = 0;
            break;
        default:
            break;
    }
}


void Map::Move() {
    // The orientation allows us to determine what the last pressed key is
    const Uint8* event_array = SDL_GetKeyboardState(nullptr);
    switch (protag_orientation_){
        case kLeft:
            // update the velocities so they increase if a key is being pressed or fall back to zero when a key isn't being pressed
            if( event_array[SDL_SCANCODE_LEFT] ) {
                if( protag_velocity_.xVel > -protag_accel_.terminalVelocity ) { // We want to limit the velocity in any direction; originally at 64
                    protag_velocity_.xVel -= protag_accel_.speedUp;
                    if( protag_velocity_.xVel < -protag_accel_.terminalVelocity ) { // We check after increasing that we are not above the limit
                        protag_velocity_.xVel = protag_accel_.terminalVelocity;
                    }
                }
            }
            else if( protag_velocity_.xVel < 0){
                protag_velocity_.xVel += protag_accel_.sloDown; // value subject to change
                // we now treat the case where we overshoot 0
                if( protag_velocity_.xVel > 0){
                    protag_velocity_.xVel = 0;
                }
            }
            break;

        case kRight:
            if( event_array[SDL_SCANCODE_RIGHT] ) {
                if( protag_velocity_.xVel < protag_accel_.terminalVelocity ) {
                    protag_velocity_.xVel += protag_accel_.speedUp;
                    if( protag_velocity_.xVel > protag_accel_.terminalVelocity ) {
                        protag_velocity_.xVel = protag_accel_.terminalVelocity;
                    }
                }
            }
            else if( protag_velocity_.xVel > 0){
                protag_velocity_.xVel -= protag_accel_.sloDown;
                if( protag_velocity_.xVel < 0){
                    protag_velocity_.xVel = 0;
                }
            }
            break;

        case kDown:
            if( event_array[SDL_SCANCODE_DOWN] ) {
                if( protag_velocity_.yVel < protag_accel_.terminalVelocity ) {
                    protag_velocity_.yVel += protag_accel_.speedUp;
                    if( protag_velocity_.yVel > protag_accel_.terminalVelocity ) {
                        protag_velocity_.yVel = protag_accel_.terminalVelocity;
                    }
                }
            }
            else if( protag_velocity_.yVel > 0){
                protag_velocity_.yVel -= protag_accel_.sloDown;
                if( protag_velocity_.yVel < 0){
                    protag_velocity_.yVel = 0;
                }
            }
            break;

        case kUp:
            if( event_array[SDL_SCANCODE_UP] ) {
                if( protag_velocity_.yVel > -protag_accel_.terminalVelocity ) {
                    protag_velocity_.yVel -= protag_accel_.speedUp;
                    if( protag_velocity_.yVel < -protag_accel_.terminalVelocity ) {
                        protag_velocity_.yVel = protag_accel_.terminalVelocity;
                    }
                }
            }
            else if( protag_velocity_.yVel < 0){
                protag_velocity_.yVel += protag_accel_.sloDown;
                if( protag_velocity_.yVel > 0){
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
}


//to check 
void Map::AddObject(Object item) {
    objects_[item.GetPosition()]= item;
}

// return the object if it was found
Object Map::RemoveObject(int obj_id){
    for(std::map<Position,Object>::iterator i = objects_.begin(); i != objects_.end(); i++){
        if ((i->second).GetObjId()==obj_id){
            Object res = i->second;
            objects_.erase(i);
            return res;
        }
    }
    return Object();
}


void Map::AddNpc(Character npc){
    npc_[npc.GetPositionPointer()]= npc;
}

Character Map::RemoveNpc(int char_id){
    for(std::map<Position*,Character>::iterator i = npc_.begin();i != npc_.end();i++){
        if ((i->second).GetCharId()==char_id){
            Character res = i->second;
            npc_.erase(i);
            return res;
        }
    }
    return Character();
}
