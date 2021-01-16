#pragma once

#include "SDL2/SDL.h"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

class Synapses;

class Clock {
  public:
    enum Status {
        Default = 0,
        DateAdvanced,
        Late,
        ClockError,
    };

    Clock();
    ~Clock() = default;

    Synapses* synapses_;

    // ---------- HOURS & MINUTES ----------
    const unsigned kStartingAbsoluteMinute = 420; // 7:00 AM
    const unsigned kLateAbsoluteMinute = 180;     // 3:00 AM
    const unsigned kMaxAbsoluteMinute = 1440;     // 24 hours

    // Minute & hour, for displaying.
    unsigned GetMinute();
    unsigned GetHour();
    unsigned GetAbsoluteMinute();
    std::string GetClockString();
    static std::string ToString(unsigned x) {
        return (x < 10 ? "0" : "") + std::to_string(x);
    };

    // Jumps to the specified absolute_minute.
    // Calls AdvanceMinute.
    Status JumpAbsoluteMinute(unsigned absolute_minute);

    // Resets to default starting hour.
    // E.g. used after Clock::Late is signalled.
    void Reset();

    // Main method of time managing. Returns DateAdvanced to
    // signal date changes.
    Status AdvanceMinute(unsigned minute_count);

    // ---------- DATES ----------
    // Dates are manually specified and saved in a list.
    struct Date {
        unsigned day_of_week, day, month, year;
    };
    const std::vector<std::string> kDaysOfWeek = {"Mon", "Tue", "Wed", "Thu",
                                                  "Fri", "Sat", "Sun"};
    const std::vector<std::string> kMonth = {"...", "Jan", "Feb", "Mar", "Apr",
                                             "May", "Jun", "Jul", "Aug", "Sep",
                                             "Oct", "Nov", "Dec"};
    Date GetDate();
    std::string GetDateString(); // e.g. Mon, Jan 17, 2020

    // Adds date to calendar_.
    void AddDate(const Date& date);

    // Demo.
    void InitializeDemo();

  private:
    unsigned absolute_minute_;
    std::vector<Date> calendar_;
    unsigned date_index_ = 0; // current index in calendar_

    // Moves to next day in calendar_. Called by AdvanceMinute.
    Status AdvanceDate();
};

struct Event {
    unsigned event_id = 0;   // default: null event
    std::string title;       // "Cours magistral: MAA205".
    std::string description; // "Tous les étudiants."
    unsigned start_time;     // in absolute_minute, 930 (15:30)
    unsigned end_time;       // in absolute_minute, 1050 (17:30)
};

struct Day {
    unsigned day_id;
    std::vector<Event> events;
    // TODO: Tasks.
    // TODO: Map modifications.
};

class Synapses {
  public:
    Synapses();

    Clock* clock_;

    void AddDay(const Day& day);
    void UpdateDay(); // called by Clock.

    std::vector<Event> GetCurrentEvents();

    // Decisions for the next event.
    unsigned IgnoreEvent(); // return event_id
    unsigned AttendEvent(); // time skip: change Clock to ending_time,
                            // return event_id

    // Interface.
    void Render();
    void HandleInput(SDL_Event event);

    // Demo.
    void InitializeDemo();

  private:
    void UpdateCurrentEvents();
    std::vector<Event> current_events_; // sorted by starting time (reverse)
    std::vector<Day> days_;             // reversed for easy next day access

    std::vector<std::string> options_ = {"Attend", "Ignore", "Skip 30 minutes"};
    size_t selected_option_ = 2;

    // TODO: Tasks.
};
