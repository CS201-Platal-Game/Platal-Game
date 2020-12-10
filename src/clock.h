#pragma once

#include <cassert>
#include <string>
#include <vector>

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

    // ---------- HOURS & MINUTES ----------
    const unsigned kStartingAbsoluteMinute = 420; // 7:00 AM
    const unsigned kLateAbsoluteMinute = 180;     // 3:00 AM
    const unsigned kMaxAbsoluteMinute = 1440;     // 24 hours

    // Minute & hour, for displaying.
    int GetMinute();
    int GetHour();
    int GetAbsoluteMinute();

    Status SetAbsoluteMinute(unsigned absolute_minute);

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
    const std::vector<std::string> kMonth = {"...", "Jan", "Feb", "Mar", "Apr", "May",
                                             "Jun", "Jul", "Aug", "Sep", "Oct",
                                             "Nov", "Dec"};
    Date GetDate();
    std::string GetDateString(); // e.g. Mon, Jan 17, 2020

    // Adds date to calendar_.
    void AddDate(Date date);

  private:
    unsigned absolute_minute_;
    std::vector<Date> calendar_;
    unsigned date_index_; // current index in calendar_

    // Moves to next day in calendar_. Called by AdvanceMinute.
    Status AdvanceDate();
};
