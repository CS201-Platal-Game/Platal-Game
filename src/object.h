#pragma once

class Object {
  public:
    struct Position {
        int x, y;
    };

    Object(int width, int height, bool collidable);
    ~Object();

    int GetWidth();
    int GetHeight();
    bool IsCollidable();
    Position GetPosition();

    // Returns a copy of the object.
    Object Copy();

    // TODO: set texture

  protected:
    int width_, height_; // dimension in squares
    bool collidable_;
    Position position_; // possibly the up-left position of the object,
                        // subject to changes

    // TODO: texture
};

// Object signalling map changes.
class Portal : public Object {
  public:
    Portal(int width, int height, int map_id);

  private:
    int map_id_;
};
