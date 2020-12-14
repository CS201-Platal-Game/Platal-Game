#include "platal_map.h"
#include "game.h" // added game.h, just in case
#include "utils/csv2map.h"
//Chris here changing stuff for the map part, changes still need to be made, 



Map::Map() {
    // The textures we have for the moment are in Platal-Game -> images ->

    //Here we will add as many textures as needed, need yet to be determined
    TextureManager::Instance()->load("dirt", "./images/maptexture/dirt.png", Game::renderer_);
    TextureManager::Instance()->load("grass", "./images/maptexture/grass.png", Game::renderer_);
    TextureManager::Instance()->load("water", "./images/maptexture/water.png", Game::renderer_);

    // sdl source and dest rects
    src_ = dest_ = {0, 0, 64, 64};

    // width and height of the map in squares
    width_ = height_ = 0;
}
// The void Map::LoadMap I think has already been coded by Carolina, if not I'll do it

void Map::LoadMap(char *filename) {
    struct MapBundle tmp;
    tmp = csv2map(filename);

    width_ = tmp.width;
    height_ = tmp.height;
    map_array_ = tmp.map_array;
}


void Map::DrawMap(Position center){
    // type here is for the type of texture, i.e 

    int type = 0;
    std::string name = "";

    for(int width = 0; width < width_ ; width +=1)
    {
        for(int height=0; height < height_ ; height +=1)
        {
            type = map_array_[width][height];

            switch(type) {
                case 1: name = "dirt" ; break;
                case 2: name = "grass"; break;
                case 3: name = "water"; break;
                default: name = ""; break;
            }
            if(name != "") 
                TextureManager::Instance()->Draw(name,src_ , {64*height, 64*width, src_.w, src_.h}, Game::renderer_);
            // Here I use TextureManager from texture_manager.cpp
        }
    }
}

//to check 
void Map::AddObject(Object item) {
    (*objects_)[item.GetPosition()]= item;
}

// return the object if it was found
Object Map::RemoveObject(int obj_id){
    for(std::map<Position,Object>::iterator i = objects_->begin(); i != objects_->end(); i++){
        if ((i->second).GetObjId()==obj_id){
            Object res = i->second;
            objects_->erase(i);
            return res;
        }
    }
    return Object();
}

void Map::AddNpc(Character npc){
    (*npc_)[npc.GetPositionPointer()]= npc;
}

Character Map::RemoveNpc(int char_id){
    for(std::map<Position*,Character>::iterator i = npc_->begin();i != npc_->end();i++){
        if ((i->second).GetCharId()==char_id){
            Character res = i->second;
            npc_->erase(i);
            return res;
        }
    }
    return Character();
}

