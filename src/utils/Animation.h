#pragma once
#include "texture_manager.h"
// The animation of sprites is not included in the texture manager so here it is

//This is a data structure used to animate a sprite
//The only difference between struct (literally 'data structure') and class
// is that here all the attributes will be public (relevant in this situation)

// I HAVE NO IDEA IF THIS WORKS (probs not)
// I CAN'T RUN IT BECAUSE MY COMPUTER WON'T COMPILE THE THING :(
// PLEASE HELP

class AnimatedTexture{
public:
    AnimatedTexture();
    AnimatedTexture(std::string id, int cFrame, int mFrame,
                    int w, int h,
                    int posX, int posY);
    ~AnimatedTexture();
    void Render(int posX, int PosY, bool reset);
    void loadFile(std::string filename);
    void Update();

private:
    int currFrame_; // current frame
    int maxFrame_; // last frame
    SDL_Rect frame_; // creates sdl rect object for frame to display
    std::string id_; // id for loading strip / image
    int x_; // indicates position where obj will be rendered
    int y_;
    // currently not necessary
    // bool animated_;

};

//Old structure
//struct Animation {
    //int id;
    //int frames; //number of frames
    //int speed; //speed of animation

    //Animation()= default; //default constructor which does nothing
    //Animation(int i, int f, int s){
      //  id = i;
      //  frames = f;
      //  speed = s;
   // };

//};

// when using this, remember that we want the initial position of the sprite, if not animated, to be 0
