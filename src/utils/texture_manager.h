#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>

class TextureManager {
  public:
    // this is Nina trying some stuff, it might be a disaster
    static SDL_Texture* Instance(){
        if (myInstance == 0){
            myInstance = new TextureManager()
        }
        return myInstance
    }
    //initialiser
    bool load(std::string, std::string, SDL_renderer*); //load the element so we are able to reference it later

    // for drawing static objects like the background image
    // takes an id, position rendered (x,y), width, height and orientation
    void draw(std::string id, int x, int y,
              int width, int height,
              SDL_Renderer* renderer,
              SDL_RendererFlip flip = SDL_FLIP_NONE )

    // for drawing objects and characters (can also be used to draw tiled objects)
    // the frames thing is to facilitate animation of characters (think of a GIF, but as one long image with multiple frames)
    void drawFrame(std::string id, int x, int y,
                   int width, int height,
                   int row, int col,
                   SDL_Renderer* renderer,
                   SDL_RendererFlip flip = SDL_FLIP_NONE)

    // delete SDL texture (yes this is a doctor who reference)
    void exterminate(std::string id);

private:
    map<std::string SDL_Texture*> m_textureMap; // map with all SDL textures
    TextureManager(){}; // make it a singleton
    ~TextureManager(); // unmake it
    static SDL_Texture* myInstance;

};

// I am calling it Mr Texture Manager so we don't get confused with the class name
typedef TextureManager MrTextureManager;

// in the event that I am overcomplicating, I'm leaving this stuff here
//static SDL_Texture* LoadTexture(const char* filename);

// take src rect from texture and draw it in the dest rect location
//static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
