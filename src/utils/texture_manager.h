#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <iostream>
#include <map>

class TextureManager {
  public:
    // this is Nina trying some stuff, it might be a disaster
    static TextureManager* Instance(){
        if (myInstance == 0){
            myInstance = new TextureManager();
        }
        return myInstance;
    }
    // Chris here adding a static for my Map part of the game, changes start here

    void Draw(std::string, SDL_Rect src_, SDL_Rect dest_, SDL_Renderer*);
      
    // Chris changes end here
      
    //initialiser
    bool load(std::string id, std::string filename, SDL_Renderer* renderer); //load the element so we are able to reference it later

    // for drawing static objects like the background image
    // takes an id, position rendered (x,y), width, height and orientation
    void draw(std::string id, int x, int y,
              int width, int height,
              SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE );

    // for drawing objects and characters (can also be used to draw tiled objects)
    // the frames thing is to facilitate animation of characters (think of a GIF, but as one long image with multiple frames)
    void drawFrame(std::string id, int x, int y,
                   int width, int height,
                   int row, int frame,
                   SDL_Renderer *renderer,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);

    // delete SDL texture (yes this is a doctor who reference)
    void exterminate(std::string id);

private:
    std::map<std::string, SDL_Texture*> textureMap; // map with all SDL textures
    TextureManager()= default;
    ~TextureManager();
    static TextureManager* myInstance;

};

// not sure this is 100% necessary but might make things easier
// if I understood correctly what I'm doing then this should let us use MyTextureManager as a typename
typedef TextureManager MyTextureManager;

// in the event that I am overcomplicating, I'm leaving this stuff here
//static SDL_Texture* LoadTexture(const char* filename);

// take src rect from texture and draw it in the dest rect location
//static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
