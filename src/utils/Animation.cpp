#include "Animation.h"
#include "texture_manager.h"
#include "game.h" 

AnimatedTexture::AnimatedTexture() {
    //default does nothing
}

AnimatedTexture::AnimatedTexture(std::string id, int cFrame, int mFrame,
                                 int w, int h,
                                 int posX, int posY) {
    currFrame_ = cFrame;
    maxFrame_ = mFrame;
    x_ = posX;
    y_ = posY;
    id_ = id;
    // animated_ = true; // this is probably not useful

    frame_.w = w; // sets the size of the rectangle
    frame_.h = h;
    frame_.x = posX;
    frame_.y = posY;
}

void AnimatedTexture::loadFile(std::string filename){
    TextureManager::Instance()->load(id_, filename, Game::renderer_);
}

void AnimatedTexture::Render(int posX, int posY, bool reset) {
    // draw a frame to the screen
    // put posX and posY just in case but it should (probably) be viewport_center.x and .y 
    if (reset){ // if you want to "force" the display of the initial frame
        frame_ = 0;
    }
    TextureManager::Instance()->DrawFrame(id_, frame_, {posX, posY, 32, 32}, Game::renderer_);
}


void AnimatedTexture::Update() {
    if (currFrame_ >= maxFrame_){
        currFrame_ = 0;
    }
    else currFrame_++
    // move onto next frame
    frame_.x = currFrame_ *  frame_.w;
}

