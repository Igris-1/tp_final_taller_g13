#ifndef LASER_RIFLE_H
#define LASER_RIFLE_H

#include "weapon_interface.h"
#include "../bullets_strategy/laser.h"

#define TILES_LASER_DISTANCE 300

class LaserRifle : public WeaponInterface {

    private:

    public:
        std::vector<BulletInterface> fire(Position start_position, Position direction){
            std::vector<BulletInterface> bullets;
            bullets.push_back(Laser(start_position, direction, TILES_LASER_DISTANCE));
            return bullets;
        }
};

#endif
