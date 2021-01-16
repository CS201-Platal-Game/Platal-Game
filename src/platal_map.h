#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "character.h"
#include "object.h"
#include "utils/structs.h"
#include "utils/texture_manager.h"
#include "utils/tiles.h"
#include <vector>
#include <map>
#include <string>
// Chris here working on platal_map objects, Since textures are not yet defined the outcome can't be tested, so I am coding for a general idea.

class Map {
  public:
    Map(); // added empty default constructor, could be changed later
    ~Map(); // the map deconstructor

    void LoadMap(char *filename, Position starting_pos); // load map from file
    void DrawMap(); // draw map to screen

    // player movement
    bool IsLegal();
    void HandleInput(SDL_Event event);
    void Move();
    void ZeroSpeed(){ protag_velocity_ = {0,0}; };

    // interactions with the npcs
    void AddNpc(Character npc);
    Character RemoveNpc(int char_id); // return the npc if it was found

    // interaction with the objects
    void AddObject(Object item);
    Object RemoveObject(int obj_id); // return the object if it was found

    int map_id_; // the name of the location the map represents
    
    void AddSwitch(Switch item);
    Switch RemoveSwitch(int obj_id);

    static Direction protag_orientation_;

  private:
    // We will probably have textures here, not yet defined
    int width_, height_; // width and height of the map, in squares
    int vpwidth_, vpheight_; // viewport dimensions
  
    //int** map_array_; // loaded from csv
    std::vector<std::vector<int>> map_array_;
    std::map<SDL_Rect, std::vector<Object>, SDLRectCompare> objects_; // map from position on screen to object
    std::map<SDL_Rect, std::vector<Switch>, SDLRectCompare> switches_; 
    std::map <Position*, Character> npc_; // map from pointers to position on screen to object
  
    SDL_Rect src_, dest_; // attributes used while rendering

    // movement
    Position center_position_;
    Velocity protag_velocity_{0,0};
    Accel protag_accel_ = {32, 8, 16};

    // backgroud music
    std::string music_;
};

