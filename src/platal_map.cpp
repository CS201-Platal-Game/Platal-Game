#include "platal_map.h" 
//Chris here changing stuff for the map part, changes still need to be made, 



Map::Map() {
    // The textures we have for the moment are in Platal-Game -> images ->

    TextureManager::Instance()->load("dirt", "maptexture/dirt.png", Game::renderer_);
    TextureManager::Instance()->load("grass", "maptexture/grass.png", Game::renderer_);
    TextureManager::Instance()->load("water", "maptexture/water.png", Game::renderer_);

     //Here we will add as many textures as needed, need yet to be determined


src_.w = src_.h = 32 ; 

}
// The void Map::LoadMap I think has already been coded by Carolina, if not I'll do it





void Map::DrawMap(Position center){
    // type here is for the type of texture, i.e 

    int type = 0;
    std::string name = "";

    for(int width = 0; width < width_ ; width +=1)
    {
        for(int height=0; height <height_ ; height +=1)
        {
            type = map_array_[width][height];

            switch(type)

            {
                case 0:
                name = "dirt" ;

                case 1:
                name = "grass";

                case 2:
                name = "water";

                default:
                name = "";
                    break;

            }
            if(name != "") 
            TextureManager::Instance()->Draw(name,src_ , dest_, Game::renderer_)  // Here I use TextureManager from texture_manager.cpp

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

