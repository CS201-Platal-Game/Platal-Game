#include "HUD.h"
#include "SDL2/SDL.h"
#include "game.h"
#include "utils/font_manager.h"
#include "utils/texture_manager.h"
#include <fstream>
#include <iostream>
#include <string>

// Chris still here making comments for myself and whoever is reading this
// Here we have a case where we don't precise the stats, can be changed to a
// specific situation if needed

std::string sleep_flavor_text(float current, float max) {
    double ratio = current / max;
    if (ratio < .25)
        return ("exhausted");
    if (ratio < .5)
        return "tired";
    if (ratio < .75)
        return "rested";
    return "well rested";
}

std::string social_flavor_text(float current, float max) {
    double ratio = current / max;
    if (ratio < .25)
        return ("shit");
    if (ratio < .5)
        return "lame";
    if (ratio < .75)
        return "good";
    return "AwEsOmE";
}

std::string quartile(float current, float max) {
    double ratio = current / max;
    if (ratio < .25)
        return ("4");
    if (ratio < .5)
        return "3";
    if (ratio < .75)
        return "2";
    return "1";
}

HUD::HUD() {
    CurrentGPA = 0.0f;
    MaxGPA = 4.2f;
    CurrentRest = 0.0f;
    MaxRest = 100.0f;
    CurrentSocial = 0.0f;
    MaxSocial = 100.0f;
    FontManager::Instance()->Load("hud_font", "./fonts/novem___.ttf", 25);
}
// Case where the GPA etc... of the character is precised

HUD::HUD(float GPA, float Rest, float Social) {
    CurrentGPA = GPA;
    MaxGPA = 4.2f;
    CurrentRest = Rest;
    MaxRest = 100.0f;
    CurrentSocial = Social;
    MaxSocial = 100.0f;
    FontManager::Instance()->Load("hud_font", "./fonts/novem___.ttf", 25);
}

// Here intially the Get functions were void, but changed to double since we
// need something returned

float HUD::GetGPA() { return CurrentGPA; }

void HUD::GPAIncrease(float change) { CurrentGPA += change; }

void HUD::GPADecrease(float change) { CurrentGPA -= change; }

void HUD::RestIncrease(float change) { CurrentRest += change; }

void HUD::RestDecrease(float change) { CurrentRest -= change; }

void HUD::SocialIncrease(float change) { CurrentSocial += change; }

void HUD::SocialDecrease(float change) { CurrentSocial -= change; }

float HUD::GetRest() { return CurrentRest; }

float HUD::GetSocial() { return CurrentSocial; }

void HUD::Render() {
    // if height = 640 and width = 800, {0 = x position of top left corner, 640
    // = y position of top left corner, 800 = width rect, 64 = height rect} The
    // width and height can be changed if needed In order to get what we want I
    // split the total width into 3 for the 3 stats, with 32 length on the
    // outsides, and between the states rendered Tried combining different
    // strings and transforming a double into a string with to_string, to give
    // essentially one sentence that can then be changed depending on stats or
    // preference

    //SDL_Rect HUD_rect = {0, 580, 900, 64};
    SDL_Rect HUD_rect = {0, 0, 900, 64};
    SDL_SetRenderDrawBlendMode(Game::renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Game::renderer_, 180, 180, 180, 100);
    SDL_RenderFillRect(Game::renderer_, &HUD_rect);

    std::string GPA_stat_string = "Quartile: " + quartile(GetGPA(), MaxGPA);
    std::string Rest_stat_string =
        "You feel " + sleep_flavor_text(GetRest(), MaxRest);
    std::string Social_stat_string =
        "Life is " + social_flavor_text(GetSocial(), MaxSocial);

    FontManager::Instance()->Draw("hud_font", GPA_stat_string, 32, 20,
                                  {16, 100, 16}, Game::renderer_);
    FontManager::Instance()->Draw("hud_font", Rest_stat_string, 288, 20,
                                  {16, 16, 100}, Game::renderer_);
    FontManager::Instance()->Draw("hud_font", Social_stat_string, 620, 20,
                                  {100, 16, 16}, Game::renderer_);
}
