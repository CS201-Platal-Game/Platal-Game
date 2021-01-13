#include "HUD.h"
#include "game.h"
#include "utils/font_manager.h"
#include "utils/texture_manager.h"
#include <fstream>
#include <iostream>
#include <string>
//Chris still here making comments for myself and whoever is reading this
//Here we have a case where we don't precise the stats, can be changed to a specific situation if needed

HUD::HUD();
	double CurrentGPA = 0;
	double MaxGPA = 4.2;
	double CurrentRest = 0;
	double MaxRest = 100;
	double CurrentSocial = 0;
	double MaxSocial = 100;

// Case where the GPA etc... of the character is precised

HUD::HUD(double GPA, double Rest, double Social){
	double CurrentGPA = GPA;
	double MaxGPA = 4.2;
	double CurrentRest = Rest;
	double MaxRest = 100;
	double CurrentSocial = Social;
	double MaxSocial = 100;


}

void HUD::GetGPA(){
	return CurrentGPA;
}

void HUD::GPAIncrease(double change){
	CurrentGPA += change;
}

void HUD::GPADecrease(double change){
	CurrentGPA -= change;
}

void HUD::RestIncrease(double change){
	CurrentRest += change;
}

void HUD::RestDecrease(double change){
	CurrentRest -= change;
}

void HUD::SocialIncrease(double change){
	CurrentSocial += change;
}

void HUD::SocialDecrease(double change){
	CurrentSocial -= change;
}

void HUD::GetRest(){
	return CurrentRest;
}

void HUD::GetSocial(){
	return CurrentSocial;
}

void HUD::render() {
// if height = 640 and width = 800, {0 = x position of top left corner, 640 = y position of top left corner, 800 = width rect, 64 = height rect} 
// The width and height can be changed if needed	
// In order to get what we want I split the total width into 3 for the 3 stats, with 32 length on the outsides, and between the states rendered
// Tried combining different strings and transforming a double into a string with to_string, to give essentially one sentence that can then be changed depending on stats or preference

	SDL_RECT HUD_rect = {0, 640, 800, 64}
	SDL_SetRenderDrawBlendMode(Game::renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Game::renderer_, 0, 0, 0, 196);
    SDL_RenderFillRect(Game::renderer_, &HUD_rect);

    GPA_stat_string = "Admin has declared your GPA to be" + std::to_string(getGPA()) + "out of" + std::to_string(MaxGPA);
    Rest_stat_string = "Today your body feels" + std::to_string(getRest()) + "rested out of " + std::to_string(MaxRest);
    Social_stat_string = "Recent Interactions have filled your social bar to" + std::to_string(getSocial()) + "out of" + std::to_string(MaxSocial);




    FontManager::Instance()->Draw("retganon", GPA_stat_string, 32, 608,
                                  {224, 16, 50}, Game::renderer_);
    FontManager::Instance()->Draw("retganon", Rest_stat_string, 288, 608,
                                  {224, 16, 50}, Game::renderer_);
    FontManager::Instance()->Draw("retganon", Social_stat_string, 544, 608,
                                  {224, 16, 50}, Game::renderer_);

}