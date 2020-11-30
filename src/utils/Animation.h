// The animation of sprites is not included in the texture manager so here it is

//This is a data structure used to animate a sprite
//The only difference between struct (literally 'data structure') and class
// is that here all the attributes will be public (relevant in this situation)


#ifndef PLATAL_GAME_ANIMATION_H
#define PLATAL_GAME_ANIMATION_H

struct Animation {
    int id;
    int frames; //number of frames
    int speed; //speed of animation

    Animation()= default; //default constructor which does nothing
    Animation(int i, int f, int s){
        id = i;
        frames = f;
        speed = s;
    };

};

// when using this, remember that we want the initial position of the sprite, if not animated, to be 0

#endif //PLATAL_GAME_ANIMATION_H
