#include "object.h"

Object::Object(int width, int height, bool collidable) {
    // Initializing all the attributes. We set x = y = 0 for the moment,
    // subject to change depening on whether or not we want it
    // as an argument in the contructor
    width_ = width;
    height_ = height;
    collidable_ = collidable;
    position_ = Position();
    position_.x = 0;
    position_.y = 0;
}

int Object::GetWidth() {
    return width_;
}

int Object::GetHeight() {
    return height_;
}

bool Object::IsCollidable() {
    return collidable_;
}

Object::Position Object::GetPosition() {
    return position_;
}

Object Object::Copy() {
    Object new_object(width_, height_, collidable_);
    return new_object;
}

Portal::Portal(int width, int height, int map_id) {
    width_ = width;
    height_ = height;
    map_id_ = map_id;
    collidable_ = false;
}