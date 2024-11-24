#ifndef POSITIONABLE_H
#define POSITIONABLE_H

#include "hitbox.h"

class Positionable {
protected:
    Hitbox hitbox;

public:
    Positionable(Hitbox& Hitbox): hitbox(hitbox) {}
    Positionable(int x, int y, int width, int height): hitbox(x, y, width, height) {}
    Positionable(): hitbox(-1, -1, 10, 10) {}

    // void move_relative_to(Position& position_movement) {
    //     this->hitbox.move_relative(position_movement.get_x(), position_movement.get_y());
    // }
    void move_relative_to(int dx, int dy) { this->hitbox.move_relative(dx, dy); }
    // void move_to(Position& new_position) {
    //     this->hitbox.move(new_position.get_x(), new_position.get_y());
    // }
    void move_to(int x, int y) { this->hitbox.move(x, y); }
    int get_x() { return this->hitbox.get_x(); }
    int get_y() { return this->hitbox.get_y(); }
    // Position get_position() { return Position(this->hitbox.get_x(), this->hitbox.get_y()); }
    Hitbox get_hitbox() { return this->hitbox; }
    Hitbox& get_reference_hitbox() { return this->hitbox; }
    int get_width() { return this->hitbox.get_width(); }
    int get_height() { return this->hitbox.get_height(); }
};

#endif
