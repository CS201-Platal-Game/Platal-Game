#include "platal_map.h"
//Chris here changing stuff for the map part, changes still need to be made, 



Map::Map() {

	// texture1 = TextureManager::LoadTexture("....")
	// Here we will add as many textures as needed, need yet to be determined

LoadMap(map_array_)
}


void Map::DrawMap(){

	int type = 0;

	for(width = 0; width < width_ ; width +=1)
	{
		for(height=0; height <height_ ; height +=1)
		{
			type = map_array_[width][height]

			switch(type)
			{
				case 0:
				TextureManager::draw(texture12345etc,src_,dest_)
				default:
					break;

			}
		}

	}
}