#ifndef AKBULLET_H
#define AKBULLET_H

#include "bullet_interface.h"

class MapGame;

class FMJ: public BulletInterface {
private:
    int moved_vertical = 0;
    bool vertical = false;

    bool next_position_vertical(MapGame& map);
public:
    FMJ(int duck_trigger_id, int x, int y, int x_direction, int y_direction, int travel_distance,
           int damage, int size, bool vertical);
    bool next_position(MapGame& map) override;
    int get_id() override;
};

#endif
