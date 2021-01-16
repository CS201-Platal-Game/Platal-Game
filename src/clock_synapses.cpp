#include "clock.h"
#include "game.h"

// ---------- SYNAPSES ----------

std::vector<Event> Synapses::GetCurrentEvents() {
    UpdateCurrentEvents();
    return current_events_;
}

void Synapses::AddDay(const Day& day) { days_.push_back(day); }

void Synapses::UpdateDay() {
    if (days_.empty()) {
        return;
    }
    Day day = days_.back();
    days_.pop_back();

    current_events_.clear();
    for (int i = (int)day.events.size() - 1; i >= 0; --i) {
        if (!current_events_.empty()) {
            assert(current_events_.back().start_time >=
                   day.events[i].start_time);
        }
        current_events_.push_back(day.events[i]);
    }
    // TODO: Task.
}

void Synapses::UpdateCurrentEvents() {
    while (!current_events_.empty() &&
           clock_->GetAbsoluteMinute() > current_events_.back().start_time) {
        current_events_.pop_back();
    } // remove events as soon as it started.
}

unsigned Synapses::IgnoreEvent() {
    if (current_events_.empty()) {
        return 0;
    }
    Event event = current_events_.back();
    current_events_.pop_back();
    return event.event_id;
}

unsigned Synapses::AttendEvent() {
    if (current_events_.empty()) {
        return 0;
    }
    Event event = current_events_.back();
    current_events_.pop_back();
    clock_->JumpAbsoluteMinute(event.end_time);
    return event.event_id;
}

void Synapses::HandleInput(SDL_Event event) {
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
        Game::game_state_ = kMenu;
        break;
    // case SDLK_RETURN:
    //     switch (selected_option_) {
    //     case 0:
    //         Continue();
    //         break;
    //     case 1:
    //         DialogueDemo();
    //         break;
    //     case 2:
    //         Quit();
    //         break;
    //     default:
    //         break;
    //     }
    //     break;
    // case SDLK_LEFT:
    //     selected_option_ -= (selected_option_ > 0);
    //     break;
    // case SDLK_RIGHT:
    //     selected_option_ += (selected_option_ < options_.size() - 1);
    //     break;
    default:
        break;
    }
}

void Synapses::Render() {
    SDL_Rect menu_rect = {0, 460, 896, 240};
    SDL_SetRenderDrawBlendMode(Game::renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Game::renderer_, 0, 0, 0, 196);
    SDL_RenderFillRect(Game::renderer_, &menu_rect);

    FontManager::Instance()->Draw("retganon", "Synapses", 20, 480,
                                  {200, 50, 50}, Game::renderer_);
    // int draw_x = 0, draw_y = 530;
    // for (size_t i = 0; i < options_.size(); ++i) {
    //     draw_x += 20;

    //     std::string current_option = options_[i];
    //     SDL_Color color = {255, 255, 255};
    //     if (i == selected_option_) {
    //         color = {175, 175, 255};
    //     }

    //     FontManager::Instance()->Draw("retganon", current_option, draw_x,
    //                                   draw_y, color, Game::renderer_);

    //     draw_x += current_option.size() * 20;
    // }
}
