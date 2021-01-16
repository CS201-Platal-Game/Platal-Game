#pragma once
#include "texture_manager.h"
#include <string>
// The animation of sprites is not included in the texture manager so here it is

//This is a data structure used to animate a sprite
//The only difference between struct (literally 'data structure') and class
// is that here all the attributes will be public (relevant in this situation)

class AnimatedTexture{
public:
    AnimatedTexture() = default;
    AnimatedTexture(std::string id, int cFrame, int mFrame,
                    int w, int h,
                    int posX, int posY);
    ~AnimatedTexture() {};
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
    int frameTime = SDL_GetTicks();
    int frameDelay = 1000/25;
};

// when using this, remember that we want the initial position of the sprite, if not animated, to be 0
