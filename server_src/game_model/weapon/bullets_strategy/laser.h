#ifndef LASER_H
#define LASER_H

#include "bullet_interface.h"

#define TILES_LASER_DISTANCE 1000

class MapGame;

class Laser: public BulletInterface {
private:
public:
    explicit Laser(int duck_trigger_id, int x, int y, int x_direction, int y_direction,
                   int travel_distance, int damage, int size);
    bool next_position(MapGame& map) override;
    int get_id() override;
};

#endif