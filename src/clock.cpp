#include "clock.h"

// ---------- HOURS & MINUTES ----------

Clock::Clock() { absolute_minute_ = kStartingAbsoluteMinute; }

unsigned Clock::GetMinute() { return absolute_minute_ % 60; }

unsigned Clock::GetHour() { return absolute_minute_ / 60; }

unsigned Clock::GetAbsoluteMinute() { return absolute_minute_; }

Clock::Status Clock::JumpAbsoluteMinute(unsigned absolute_minute) {
    if (absolute_minute >= kMaxAbsoluteMinute) {
        return ClockError;
    }
    if (absolute_minute > kLateAbsoluteMinute &&
        absolute_minute < kStartingAbsoluteMinute) { // 4AM-7AM
        return ClockError;
    }
    if (absolute_minute < absolute_minute_) {
        return ClockError;
    }
    AdvanceMinute(absolute_minute - absolute_minute_);
    return Default;
}

void Clock::Reset() { absolute_minute_ = kStartingAbsoluteMinute; }

Clock::Status Clock::AdvanceDate() {
    if (date_index_ + 1 >= calendar_.size()) {
        return ClockError;
    }
    date_index_ += 1;
    absolute_minute_ %= kMaxAbsoluteMinute;
    synapses_->UpdateDay();
    return Default;
}

Clock::Status Clock::AdvanceMinute(unsigned minute_count) {
    absolute_minute_ += minute_count;
    if (absolute_minute_ > kMaxAbsoluteMinute) {
        Status S = AdvanceDate();
        if (S != Default) {
            return S;
        }
        if (absolute_minute_ >= kLateAbsoluteMinute) {
            absolute_minute_ = kLateAbsoluteMinute;
            return Late;
        }
        return DateAdvanced;
    }
    return Default;
}

// ---------- DATES ----------

Clock::Date Clock::GetDate() {
    assert(calendar_.size() > 0);
    return calendar_[date_index_];
}

std::string Clock::GetDateString() {
    std::string date_string = "";
    Date date = GetDate();
    date_string += kDaysOfWeek[date.day_of_week] + ", ";
    date_string += kMonth[date.month] + " ";
    date_string += std::to_string(date.day) + ", ";
    date_string += std::to_string(date.year);
    return date_string;
}

void Clock::AddDate(const Clock::Date& date) {
    if (calendar_.empty()) {
        date_index_ = 0;
    } else {
        date_index_++;
    }
    calendar_.push_back(date);
}

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
