#pragma once

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