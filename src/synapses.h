#pragma once

#include <string>

struct Event {
    unsigned event_id;
    std::string title;       // "Cours magistral: MAA205".
    std::string description; // "Tous les étudiants."
    unsigned start_time;     // in absolute_minute, 930 (15:30)
    unsigned end_time;       // in absolute_minute, 1050 (17:30)
};

class Day {
};