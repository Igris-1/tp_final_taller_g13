#ifndef PEW_PEW_H
#define PEW_PEW_H
#include "weapon_interface.h"
#include "../bullets_strategy/laser.h"
#include "../bullets_strategy/bullet_interface.h"

#define TILES_LASER_DISTANCE 300

class PewPew : public WeaponInterface {
    private:

    public:
        PewPew() { }
        std::vector<BulletInterface> fire(Position start_position, Position direction) {
            std::vector<BulletInterface> bullets;
            bullets.push_back(Laser(start_position, direction, TILES_LASER_DISTANCE));
            bullets.push_back(Laser(start_position, direction + Position(1,0), TILES_LASER_DISTANCE));
            bullets.push_back(Laser(start_position, direction + Position(-1,0), TILES_LASER_DISTANCE));
            return bullets;
        }
};

#endif