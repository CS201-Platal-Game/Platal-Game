#pragma once

#include "utils/structs.h"

#include <cassert>
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
    ~Clock();

    Synapses* synapses_;

    // ---------- HOURS & MINUTES ----------
    const unsigned kStartingAbsoluteMinute = 420; // 7:00 AM
    const unsigned kLateAbsoluteMinute = 180;     // 3:00 AM
    const unsigned kMaxAbsoluteMinute = 1440;     // 24 hours

    // Minute & hour, for displaying.
    unsigned GetMinute();
    unsigned GetHour();
    unsigned GetAbsoluteMinute();

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

  private:
    unsigned absolute_minute_;
    std::vector<Date> calendar_;
    unsigned date_index_; // current index in calendar_

    // Moves to next day in calendar_. Called by AdvanceMinute.
    Status AdvanceDate();
};

class Synapses {
  public:
    Clock* clock_;

    void AddDay(const Day& day);
    void UpdateDay(); // called by Clock.

    std::vector<Event> GetCurrentEvents();

    // Decisions for the next event.
    unsigned IgnoreEvent(); // return event_id
    unsigned AttendEvent(); // time skip: change Clock to ending_time,
                            // return event_id

  private:
    void UpdateCurrentEvents();
    std::vector<Event> current_events_; // sorted by starting time (reverse)
    std::vector<Day> days_;             // reversed for easy next day access
    // TODO: Tasks.
};
