#ifndef POSITIONABLE_H
#define POSITIONABLE_H

#include "position.h"
#include <iostream>

class Positionable {
protected:
    Position position;

public:
    Positionable(int x, int y): position(x, y) {}
    //explicit Positionable(bool valid): position(-1, -1), valid(valid) {}
    Positionable(): position(-1, -1) {}

    // devuelve la posicion final y setea la nueva posicion
    Position move_relative_to(const Position& position_movement) {
        this->position = position_movement + this->position;
        std::cout << "Positionable::move_relative_to: " << this->position.get_x() << std::endl;
        return this->position; 
    }
    Position move_to(const Position& new_position) {
        this->position = new_position;
        return new_position;
    }
    bool is_in_a_live_position() { return this->position == Position(-1, -1); }
    //virtual bool is_valid() {return true;}
    
    Position get_position() { return this->position; }
};

#endif
