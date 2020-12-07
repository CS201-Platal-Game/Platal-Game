#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "character.h"
#include "object.h"
#include "utils/structs.h"
#include <vector>
#include <map>
// Chris here working on platal_map objects, Since textures are not yet defined the outcome can't be tested, so I am coding for a general idea.

class Map {
  public:
    Map() {}; // added empty default constructor, could be changed later
    ~Map(); // the map deconstructor

    void LoadMap(char *filename); // load map from file
    void DrawMap(Position position); // draw map to screen

    // interactions with the npcs
    void AddNpc(Character npc);
    Character RemoveNpc(int char_id); // return the npc if it was found

    // interaction with the objects
    void AddObject(Object item);
    Object RemoveObject(int obj_id); // return the object if it was found

    int map_id_; // the name of the location the map represents

  private:
    // We will probably have textures here, not yet defined
    int width_, height_; // width and height of the map, in squares
    int** map_array_; // loaded from csv
    std::map <Position, Object> *objects_; // map from position on screen to object
    SDL_Rect src_, dest_; // attributes used while rendering
    // SDL_Texture* texture1
    // SDL_Texture* texture2 
};

