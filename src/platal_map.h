#pragma once
#include "character.h"
#include "game.h"
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

    readonly int map_id_; // the location of the map

  private:
    int width_, height_; // width and height of the map, in squares
    int **map_array_; // loaded from csv
    std::vector<Character> *npc_;       // TODO think about implementation some more
    std::vector<Object> *objects_;      // TODO think about implementation some more
    SDL_Rect src_, dest_; // attributes used while rendering
};
