#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "character.h"
#include "object.h"
#include <vector>

class Map {
  public:
    Map();
    ~Map();

    void LoadMap(char *filename); // load map from file
    void DrawMap(); // draw map to screen

    // interactions with the npcs
    void AddNpc(Character npc);
    Character RemoveNpc(int char_id); // return the npc if it was found

    // interaction with the objects
    void AddObject(Object item);
    Object RemoveObject(int obj_id); // return the object if it was found

    int map_id_; // the name of the location the map represents

  private:
    int width_, height_; // width and height of the map, in squares
    int** map_array_; // loaded from csv

    //std::vector<Character> *npc_       // TODO think about implementation some more
    //std::vector<Object> *objects_     // TODO think about implementation some more 

    // decided it should be a map instead of vectors,
    // map from position on screen to object
    // std::map<(int,int), Object> *objects_;

    SDL_Rect src_, dest_; // attributes used while rendering
};
