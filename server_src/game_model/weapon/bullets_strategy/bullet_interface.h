#ifndef BULLET_INTERFACE_H
#define BULLET_INTERFACE_H

#include <iostream>

#include "../../../../common_src/duck_DTO.h"
#include "../../positionable.h"
// "../../../../common_src/duck_DTO.h" esto esta bien

class MapGame;

class BulletInterface: public Positionable {
protected:
    int x_direction;
    int y_direction;
    int travel_distance;
    int duck_trigger_id;
    bool bounce_count = false;
    int damage = 10;

public:
    BulletInterface(int duck_trigger_id, int x, int y, int x_direction, int y_direction);

    int get_x_direction();

    int get_y_direction();

    Hitbox get_hitbox();

    bullet_DTO to_DTO();

    // devuelve true si se puede mover. false si no se puede mover mas
    virtual bool next_position(MapGame& map) = 0;
    virtual int get_id() = 0;

    int damage_generated(int duck_id);
};

#endif
