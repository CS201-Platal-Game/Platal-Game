#pragma once

struct Position {
    int x, y;

    bool operator<(Position other) {
        return ((x < other.x) && (y < other.y));
    }

    bool operator<=(Position other) {
      return ((x <= other.x) && (y <= other.y));
    }

    bool operator>(Position other) {
      return ((x > other.x) && (y > other.y));
    }

    bool operator>=(Position other) {
      return ((x >= other.x) && (y >= other.y));
    }

    bool operator==(Position other) {
      return ((x == other.x) && (y == other.y));
    }
};