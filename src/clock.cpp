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
