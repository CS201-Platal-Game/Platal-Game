#pragma once

#include "SDL2/SDL.h"
#include <string>
#include <vector>

struct Position {
    int x, y;

    bool operator<(const Position& other) const {
        return ((x < other.x) && (y < other.y));
    }

    bool operator<=(const Position& other) const {
        return ((x <= other.x) && (y <= other.y));
    }

    bool operator>(const Position& other) const {
        return ((x > other.x) && (y > other.y));
    }

    bool operator>=(const Position& other) const {
        return ((x >= other.x) && (y >= other.y));
    }

    bool operator==(const Position& other) const {
        return ((x == other.x) && (y == other.y));
    }
};

struct Velocity {
    int xVel, yVel;
};

struct Accel {
    int terminalVelocity, speedUp, sloDown;
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

struct SDLRectCompare {
	bool operator()(const SDL_Rect& r1, const SDL_Rect& r2) const {
		if (r1.x != r2.x)
		{
			return r1.x < r2.x;
		}
		
		if (r1.y != r2.y)
		{
			return r1.y < r2.y;
		}
		
		if (r1.w != r2.w)
		{
			return r1.w < r2.w;
		}
		
		return r1.h < r2.h;
	}
};
