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

    // devuelve la posicion actual y setea la nueva posicion
    Position move_to(Position new_position) {
        Position aux = position;
        position = new_position;
        return aux;
    }
    bool is_in_a_live_position() { return this->position == Position(-1, -1); }

    bool is_valid() { return this->valid; }

    Position get_position() { return this->position; }
};
