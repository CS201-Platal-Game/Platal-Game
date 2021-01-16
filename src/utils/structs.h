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

struct SDLRectCompare {
    bool operator()(const SDL_Rect& r1, const SDL_Rect& r2) const {
        if (r1.x != r2.x) {
            return r1.x < r2.x;
        }
        if (r1.y != r2.y) {
            return r1.y < r2.y;
        }
        if (r1.w != r2.w) {
            return r1.w < r2.w;
        }
        return r1.h < r2.h;
    }
};
