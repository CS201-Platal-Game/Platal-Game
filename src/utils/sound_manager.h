#pragma once
#include "SDL2/SDL_mixer.h"
#include <iostream>
#include <map>

#ifndef PLATAL_GAME_SOUND_MANAGER_H
#define PLATAL_GAME_SOUND_MANAGER_H

class SoundManager {
  public:
    static SoundManager* Instance() {
        if (myInstance == 0)
            myInstance = new SoundManager();
        return myInstance;
    }

    // loads a font element
    bool LoadMusic(std::string id, std::string filename);

    bool LoadChunk(std::string id, std::string filename);

    void PlayMusic(std::string id);
    void ToggleMusic();
    bool IsPlaying() { return Mix_PlayingMusic() != 0; };
    void PlayChunk(std::string id);

    int GetVolume() { return Mix_VolumeMusic(-1); }
    void SetVolume(int8_t vol) { Mix_VolumeMusic(vol); }

    void ExterminateMusic(std::string id);
    void ExterminateChunk(std::string id);

    ~SoundManager() { myInstance->Clean(); };
    void Clean();

  private:
    std::map<std::string, Mix_Chunk*> ChunkMap;
    std::map<std::string, Mix_Music*> MusicMap;
    SoundManager() = default;

    static SoundManager* myInstance;
};

#endif // PLATAL_GAME_SOUND_MANAGER_H