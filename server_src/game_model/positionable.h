#pragma once

#include "position.h"

class Positionable {
protected:
    Position position;
    bool valid;

public:
    Positionable(int x, int y): position(x, y), valid(false) {}
    explicit Positionable(bool valid): position(-1, -1), valid(valid) {}
    Positionable(): position(-1, -1), valid(false) {}

    // devuelve la posicion final y setea la nueva posicion
    Position move_relative_to(const Position& position_movement) {
        this->position = position_movement + this->position;
        return this->position; 
    }
    Position move_to(const Position& new_position) {
        this->position = new_position;
        return new_position;
    }
    bool is_in_a_live_position() { return this->position == Position(-1, -1); }

    bool is_valid() { return this->valid; }

    Position get_position() { return this->position; }
};
