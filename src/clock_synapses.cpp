#include "clock.h"
#include "game.h"

// ---------- SYNAPSES ----------

Synapses::Synapses() {
    // NOTE: for demo purposes.
    InitializeDemo();
}

void Synapses::InitializeDemo() {
    Event event21 = {21, "Cours magistral: MAA203", "Tous les étudiants.", 480,
                     600};
    Event event23 = {23, "Cours magistral: CSE201", "Tous les étudiants.", 795,
                     915};

    current_events_.push_back(event23);
    current_events_.push_back(event21);
}

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
        selected_option_ = 2; // no event to ignore or attend
        return 0;
    }
    Event event = current_events_.back();
    current_events_.pop_back();
    return event.event_id;
}

unsigned Synapses::AttendEvent() {
    if (current_events_.empty()) {
        selected_option_ = 2; // no event to ignore or attend
        return 0;
    }
    Event event = current_events_.back();
    current_events_.pop_back();
    clock_->JumpAbsoluteMinute(event.end_time);
    UpdateCurrentEvents();
    return event.event_id;
}

void Synapses::HandleInput(SDL_Event event) {
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
        Game::game_state_ = kMenu;
        break;
    case SDLK_RETURN:
        switch (selected_option_) {
        case 0:
            AttendEvent();
            break;
        case 1:
            IgnoreEvent();
            break;
        case 2:
            clock_->AdvanceMinute(30);
            break;
        default:
            break;
        }
        break;
    case SDLK_LEFT:
        if (current_events_.empty()) {
            selected_option_ = 2;
            break;
        }
        selected_option_ -= (selected_option_ > 0);
        break;
    case SDLK_RIGHT:
        if (current_events_.empty()) {
            selected_option_ = 2;
            break;
        }
        selected_option_ += (selected_option_ < options_.size() - 1);
        break;
    default:
        break;
    }
}

void Synapses::Render() {
    // viewport: 896 x 640
    SDL_Rect menu_rect = {0, 64, 896, 640};
    SDL_SetRenderDrawBlendMode(Game::renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Game::renderer_, 0, 0, 0, 196);
    SDL_RenderFillRect(Game::renderer_, &menu_rect);

    int left_padding = 20;
    int top_padding = 84;
    int draw_x = left_padding, draw_y = top_padding;

    FontManager::Instance()->Draw("retganon", "Synapses", draw_x, draw_y,
                                  {200, 50, 50}, Game::renderer_);

    // first line, time and date
    draw_y += 50;
    std::string clock_string = "It's " + clock_->GetClockString() + ". ";
    std::string date_string = "Today is " + clock_->GetDateString() + ". ";

    FontManager::Instance()->Draw("retganon", clock_string + date_string,
                                  draw_x, draw_y, {255, 255, 255},
                                  Game::renderer_);

    // second line, number of events
    draw_y += 50;
    std::string event_count_string;

    if (current_events_.empty()) {
        event_count_string = "You're free for the day.";
    } else {
        event_count_string = "There's " +
                             std::to_string(current_events_.size()) +
                             " upcoming event(s):";
    }
    FontManager::Instance()->Draw("retganon", event_count_string, draw_x,
                                  draw_y, {80, 80, 200}, Game::renderer_);

    SDL_Color event_color = {220, 220, 220};

    // list of events
    for (int i = (int)current_events_.size() - 1; i >= 0; --i) {
        Event event = current_events_[i];
        unsigned start_hour = event.start_time / 60,
                 start_minute = event.start_time % 60;
        unsigned end_hour = event.end_time / 60,
                 end_minute = event.end_time % 60;
        std::string start_string =
            Clock::ToString(start_hour) + ":" + Clock::ToString(start_minute);
        std::string end_string =
            Clock::ToString(end_hour) + ":" + Clock::ToString(end_minute);
        std::string time_string = "[" + start_string + "->" + end_string + "] ";

        draw_y += 50;
        FontManager::Instance()->Draw("retganon", time_string + event.title,
                                      draw_x, draw_y, event_color,
                                      Game::renderer_);

        event_color = {180, 180, 180}; // muted color for the next events
    }

    // synapses options
    draw_y += 50;
    FontManager::Instance()->Draw("retganon", "Your decision:", draw_x, draw_y,
                                  {80, 80, 200}, Game::renderer_);

    draw_y += 50;
    for (size_t i = 0; i < options_.size(); ++i) {
        std::string current_option = options_[i];
        // Highlighting.
        SDL_Color color = {180, 180, 180};
        if (i == selected_option_) {
            color = {175, 175, 255};
        }

        FontManager::Instance()->Draw("retganon", current_option, draw_x,
                                      draw_y, color, Game::renderer_);

        // Spacing for next option.
        draw_x += current_option.size() * 15 + 50;
    }

    draw_x = left_padding; // reset draw_x
}
