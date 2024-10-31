#ifndef BULLET_INTERFACE_H
#define BULLET_INTERFACE_H

#include "../../position.h"
#include "../../positionable.h"

class BulletInterface : public Positionable{
    protected:
        Position direction;
        int tiles_acount;
    public:
        BulletInterface(Position start_position, Position direction, int tiles_acount) : Positionable(start_position) {
            this->direction = direction;
            this->tiles_acount = tiles_acount;
        }
        virtual Position next_position();
        Position get_direction() { return this->direction; }
        bool is_dead() { return this->tiles_acount == 0; }

};

#endif

