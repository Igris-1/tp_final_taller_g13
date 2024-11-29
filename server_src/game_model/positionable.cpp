#include "positionable.h"

Positionable::Positionable(Hitbox& Hitbox): hitbox(hitbox) {}

Positionable::Positionable(int x, int y, int width, int height): hitbox(x, y, width, height) {}

Positionable::Positionable(): hitbox(DEFAULT_X, DEFAULT_Y, DEFAULT_WIDTH, DEFAULT_HEIGHT) {}

void Positionable::move_relative_to(int dx, int dy) {
    this->hitbox.move_relative(dx, dy);
}

void Positionable::move_to(int x, int y) {
    this->hitbox.move(x, y); 
}

int Positionable::get_x() {
    return this->hitbox.get_x();
}

int Positionable::get_y() {
    return this->hitbox.get_y();
}

Hitbox Positionable::get_hitbox() {
    return this->hitbox;
}

Hitbox& Positionable::get_reference_hitbox() {
    return this->hitbox;
}

int Positionable::get_width() { 
    return this->hitbox.get_width();
}

int Positionable::get_height() {
    return this->hitbox.get_height();
}