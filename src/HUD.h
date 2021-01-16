#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <map>
#include <string>
#include <utility>
#include <vector>

class HUD {
  public:
    HUD();
    ~HUD() = default;
    HUD(float CurrentGPA, float CurrentRest, float CurrentSocial);

    float GetGPA();
    float GetRest();
    float GetSocial();
    void Render();
    void GPAIncrease(float change);
    void GPADecrease(float change);
    void RestIncrease(float change);
    void RestDecrease(float change);
    void SocialIncrease(float change);
    void SocialDecrease(float change);

  private:
    float CurrentGPA;
    float MaxGPA;
    float CurrentRest;
    float MaxRest;
    float CurrentSocial;
    float MaxSocial;
};
