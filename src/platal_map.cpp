#include "platal_map.h" 
//Chris here changing stuff for the map part, changes still need to be made, 



Map::Map() {
    // The textures we have for the moment are in Platal-Game -> images ->

    TextureManager::load("dirt", "maptexture/dirt.png", Game::renderer);
    TextureManager::load("grass", "maptexture/grass.png", Game::renderer);
    TextureManager::load("water", "maptexture/water.png", Game::renderer);

     //Here we will add as many textures as needed, need yet to be determined

LoadMap(map_array_);

src_.width_ = src_.height_ = 32 ; 

}
// The void Map::LoadMap I think has already been coded by Carolina, if not I'll do it





void Map::DrawMap(){
    // type here is for the type of texture, i.e 

    int type = 0;
    std::string name = "";

    for(width = 0; width < width_ ; width +=1)
    {
        for(height=0; height <height_ ; height +=1)
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
            TextureManager::Draw(name,src_ , dest_, Game::renderer)  // Here I use TextureManager from texture_manager.cpp

        }

    }
}