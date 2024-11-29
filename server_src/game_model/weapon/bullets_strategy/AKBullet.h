#ifndef AKBULLET_H
#define AKBULLET_H

#include "bullet_interface.h"

class MapGame;


class AKBullet: public BulletInterface {
private:
    int dispersion;
    int counter_dispersion = 5;
public:
    AKBullet(int duck_trigger_id, int x, int y, int x_direction, int y_direction, int travel_distance,
           int damage, int size, int dispersion);
    bool next_position(MapGame& map) override;
    int get_id() override;
};

#endif
