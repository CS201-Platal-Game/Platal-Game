#include "object.h"
#include "game.h"
#include "utils/texture_manager.h"

Object::Object() {} // TODO
Object::~Object() {}

Object::Object(int width, int height, bool collidable) {
    // Initializing all the attributes. We set x = y = 0 for the moment,
    // subject to change depending on whether or not we want it
    // as an argument in the constructor
    hitbox_.x = 0;
    hitbox_.y = 0;
    hitbox_.w = width;
    hitbox_.h = height;
    collidable_ = collidable;
    position_ = {0, 0};
}

Object::Object(int width, int height, bool collidable, int x, int y ) {
    // Initializing all the attributes. We set x = y = 0 for the moment,
    // subject to change depending on whether or not we want it
    // as an argument in the constructor
    hitbox_.x = 0;
    hitbox_.y = 0;
    hitbox_.w = width;
    hitbox_.h = height;
    collidable_ = collidable;
    position_ = {x, y};
}

int Object::GetWidth() {
    return hitbox_.w;
}

int Object::GetHeight() {
    return hitbox_.h;
}

int Object::GetObjId() {
    return obj_id;
}

bool Object::IsCollidable() {
    return collidable_;
}

Position Object::GetPosition() {
    return position_;
}

Object Object::Copy() {
    Object new_object(hitbox_.w, hitbox_.h, collidable_);
    return new_object;
}

bool Object::InteractCollision(Character character) {
    // Checks if the object is collidable and if the character is currently colliding with it.

    // We haven't yet done the position and width/height attributed for the character class,
    // hence I set them as true for the moment
    bool width_condition = true;  // position_.x < character.position_.x + character.rect_w && character.position_.x < position_.x + width_
    bool height_condition = true; // position_.y < character.position_.y + character.rect_h && character.position_.y < position_.y + height_
    bool x_collision = false;
    bool y_collision = false;
    if (height_condition) {
        y_collision = true;
    } else if (width_condition) {
        x_collision = true;
    }
    if (collidable_ && (y_collision || x_collision)) {
        // Might want to prevent the character from moving if there is a collision
    }
    return (x_collision || y_collision);
}

void Object::Render() {
    TextureManager::Instance()->DrawFrame(textureId_, {32, 0, 32, 32},
                                          {position_.x, position_.y, 32, 32},
                                          Game::renderer_);

}

Portal::Portal(int width, int height, int map_id) {
    hitbox_.w = width;
    hitbox_.h = height;
    map_id_ = map_id;
    collidable_ = false;
}
