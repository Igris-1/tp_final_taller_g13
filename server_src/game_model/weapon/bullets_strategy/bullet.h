#ifndef BULLET_H
#define BULLET_H

#include "bullet_interface.h"

class MapGame;


class Bullet: public BulletInterface {
private:
public:
    Bullet(int duck_trigger_id, int x, int y, int x_direction, int y_direction,
           int travel_distance);
    bool next_position(MapGame& map) override;
    int get_id() override;
};

#endif
