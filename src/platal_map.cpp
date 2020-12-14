#include "platal_map.h"
#include "utils/texture_manager.h"
#include "game.h"


//Chris here changing stuff for the map part, changes still need to be made, 
// texture1 = TextureManager::LoadTexture("....")
// Here we will add as many textures as needed, need yet to be determined

// Nina has completely forgotten how to use the texture manager pls help
// grasstile_oneleaf_ = TextureManager::load("grass1", "grasstile_oneleaf.png", Game::renderer_); //load the element so we are able to reference it later


void Map::DrawMap(Position position) {

    int type = 0;

    for(int width = 0; width < width_ ; width +=1){
        for(int height=0; height <height_ ; height +=1){
            type = map_array_[width][height];
            switch(type) {
            case 0:
                // TextureManager::draw(texture12345etc,src_,dest_);
            default:
                break;
            }
	}
    }
}


/*  void Map::AddObject(Object item){
    
    (*objects_)[item.GetPosition()]= item;
}*/



// return the object if it was found
Object Map::RemoveObject(int obj_id){
    for(std::map<Position,Object>::iterator i = objects_->begin();i != objects_->end();i++){
        if ((i->second).GetObjId()==obj_id){
            return i->second;
        }
    }
    return Object();
}
