#ifndef EXPLOTION_H
#define EXPLOTION_H

#include "bullet_interface.h"

class MapGame;


class Explotion: public BulletInterface {
private:
public:
    Explotion(int duck_trigger_id, int x, int y, int x_direction, int y_direction,
           int travel_distance, int damage, int size);
    bool next_position(MapGame& map) override;
    int get_id() override;
};

#endif