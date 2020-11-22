#include "object.h"

Object::Object(int width, int height, bool collidable) {
    width_ = width;
    height_ = height;
    collidable_ = collidable;
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

