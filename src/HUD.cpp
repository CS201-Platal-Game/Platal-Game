#include "HUD.h"
#include "SDL2/SDL.h"
#include "game.h"
#include "utils/font_manager.h"
#include <string>

std::string sleep_flavor_text(float current, float max) {
    float ratio = current / max;
    if (ratio < .25)
        return ("exhausted");
    if (ratio < .5)
        return "tired";
    if (ratio < .75)
        return "rested";
    return "well rested";
}

std::string social_flavor_text(float current, float max) {
    float ratio = current / max;
    if (ratio < .25)
        return ("shit");
    if (ratio < .5)
        return "lame";
    if (ratio < .75)
        return "good";
    return "AwEsOmE";
}

std::string quartile(float current, float max) {
    float ratio = current / max;
    if (ratio < .25)
        return "4";
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

HUD::HUD(float GPA, float Rest, float Social) {
    CurrentGPA = GPA;
    MaxGPA = 4.2f;
    CurrentRest = Rest;
    MaxRest = 100.0f;
    CurrentSocial = Social;
    MaxSocial = 100.0f;
    FontManager::Instance()->Load("hud_font", "./fonts/novem___.ttf", 25);
}

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
    SDL_Rect HUD_rect = {0, 0, 900, 64};
    SDL_SetRenderDrawBlendMode(Game::renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Game::renderer_, 180, 180, 180, 100);
    SDL_RenderFillRect(Game::renderer_, &HUD_rect);

    std::string GPA_stat_string = "Quartile: " + quartile(GetGPA(), MaxGPA);
    std::string Rest_stat_string =
        "You feel " + sleep_flavor_text(GetRest(), MaxRest);
    std::string Social_stat_string =
        "Life is " + social_flavor_text(GetSocial(), MaxSocial);

    int gpax, restx, socialx;
    gpax = (300 - FontManager::Instance()->RenderWidth("hud_font", GPA_stat_string)) / 2;
    restx = 300 + (300 - FontManager::Instance()->RenderWidth("hud_font", Rest_stat_string)) / 2;
    socialx = 600 + (FontManager::Instance()->RenderWidth("hud_font", Social_stat_string)) / 2;

    FontManager::Instance()->Draw("hud_font", GPA_stat_string, gpax, 20,
                                  {16, 100, 16}, Game::renderer_);
    FontManager::Instance()->Draw("hud_font", Rest_stat_string, restx, 20,
                                  {16, 16, 100}, Game::renderer_);
    FontManager::Instance()->Draw("hud_font", Social_stat_string, socialx, 20,
                                  {100, 16, 16}, Game::renderer_);
}
