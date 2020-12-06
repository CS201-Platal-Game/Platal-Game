#include "platal_map.h"

Map::Map() {}

void Map::DrawMap() {}


// void Map::AddObject(Object item){}



// return the object if it was found
Object Map::RemoveObject(int obj_id){
    for(std::map<Position,Object>::iterator i = objects_->begin();i != objects_->end();i++){
        if ((i->second).GetObjId()==obj_id){
            return i->second;
        }
    }
    return Object();
}