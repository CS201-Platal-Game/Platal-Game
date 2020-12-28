#include "Animation.h"
#include "texture_manager.h"
#include "game.h" // I don't know why it won't let me access game.h

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
    animated_ = true; // not sure whether to initialise as true or false, actually

    frame_.w = w; // sets the size of the rectangle
    frame_.h = h;
    frame_.x = posX;
    frame_.y = posY;

}

void AnimatedTexture::loadFile(std::string filename){
    TextureManager::Instance()->load(id_, filename, Game::renderer_);
}

void AnimatedTexture::Render(int posX, int posY) {
    // draw a frame to the screen
    // not sure if viewport_center.x and .y is the right choice here
    // actually not sure if 32x32 is right either
    TextureManager::Instance()->DrawFrame(id_, frame_, {viewport_center_.x, viewport_center_.y, 32, 32}, Game::renderer_);
}

void AnimatedTexture::Update() {
    if (currFrame_ > maxFrame_){
        currFrame_ = 0;
    }

    // move onto next frame
    frame_.x = currFrame_ *  frame_.w;
}

