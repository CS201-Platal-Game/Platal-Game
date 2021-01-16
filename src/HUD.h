#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <utility>
#include <vector>
#include <map>


// Chris here , the goal of the HUD will be to first draw a rectangle that takes up the whole width of the screen at the top of it.
// Once that rectangle is set, we want to draw inside the different stats of our character.
// There should probably those stats in the private part of the function, and we take a function of the style GetGPA , etc..., which we use to then draw
// Render will thus be needed, with Get functions.

// Need to consider maybe cases

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
		// Here we can rename the variables accordingly
        float CurrentGPA;
        float MaxGPA;
        float CurrentRest;
        float MaxRest;
        float CurrentSocial;
        float MaxSocial;

};
