#pragma once

#include <string>
#include <vector>

class Clock {
  public:
    enum Status {
        Default = 0,
        DateAdvanced,
    };

    Clock();
    ~Clock();

    // ---------- HOURS & MINUTES ----------
    const unsigned kStartingAbsoluteMinute = 420; // 7:00 AM
    const unsigned kEndingAbsoluteMinute = 180;   // 3:00 AM

    // Minute & hour, for displaying.
    int GetMinute(); // absolute_minute % 60
    int GetHour();   // absolute_minute / 60
    int GetAbsoluteMinute();

    // Main method of time managing. Returns DateAdvanced to
    // signal date changes.
    Status AdvanceMinute(int minute_count);

    // ---------- DATES ----------
    // Dates are manually specified and saved in a list.
    struct Date {
        unsigned day_of_week, day, month, hour;
    };

    const std::vector<std::string> kDaysOfWeek = {"Mon", "Tue", "Wed", "Thu",
                                                  "Fri", "Sat", "Sun"};
    Date GetDate();
    std::string GetDateString(); // e.g. Mon, Jan 17, 2020

    // Adds date to calendar_.
    void AddDate(Date date);

  private:
    unsigned absolute_minute_;
    std::vector<Date> calendar_;
    unsigned date_index_; // current index in calendar_

    // Resets to default starting hour. Called by AdvanceMinute.
    void Reset();

    // Moves to next day in calendar_. Called by AdvanceMinute.
    void AdvanceDate();
};