#ifndef LASER_H
#define LASER_H

#include "bullet_interface.h"

class Laser: public BulletInterface{
    private:

    public:
        Laser(Position start_position, Position direction, int tiles_acount) : BulletInterface(start_position, direction, tiles_acount) {
        }
        Position next_position() {
            if(this->tiles_acount == 0) return this->position;
            return this->position + this->direction;
            this->tiles_acount--;
        }
};

#endif