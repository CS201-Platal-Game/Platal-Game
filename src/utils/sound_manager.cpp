#include "sound_manager.h"

bool SoundManager::LoadMusic(std::string id, std::string filename){
    Mix_Music* moosic;
    moosic =  Mix_LoadMUS(filename.c_str());
    
    if(!moosic) {
        std::cout << "couldn't load " << id << " music" << std::endl;
        return false;
    }

    MusicMap[id] = moosic;
    return true;
}
    
bool SoundManager::LoadChunk(std::string id, std::string filename){
    Mix_Chunk* noise;
    noise =  Mix_LoadWAV(filename.c_str());
    
    if(!noise) {
        std::cout << "couldn't load " << id << " sound" << std::endl;
        return false;
    }

    ChunkMap[id] = noise;
    return true;
}

void SoundManager::PlayMusic(std::string id){
    Mix_PlayMusic( MusicMap[id], -1 );
    
}
void SoundManager::ToggleMusic(){
    if( Mix_PausedMusic() == 1 )
        {
            //Resume the music
            Mix_ResumeMusic();
        }
        //If the music is playing
        else
        {
            //Pause the music
            Mix_PauseMusic();
        }
}

void SoundManager::PlayChunk(std::string id){
    Mix_PlayChannel( -1, ChunkMap[id], 0 );
}

void SoundManager::ExterminateMusic(std::string id){
    MusicMap.erase(id);
}
void SoundManager::ExterminateChunk(std::string id){
    ChunkMap.erase(id);
}

void SoundManager::Clean(){
    Mix_Music* mus;
    auto iter = MusicMap.begin();
    while (iter != MusicMap.end()) {
        mus = iter->second;
        Mix_FreeMusic( mus );
        iter++;
    }

    Mix_Chunk* chk;
    auto iter2 = ChunkMap.begin();
    while (iter2 != ChunkMap.end()) {
        chk = iter2->second;
        Mix_FreeChunk( chk );
        iter2++;
    }
}

