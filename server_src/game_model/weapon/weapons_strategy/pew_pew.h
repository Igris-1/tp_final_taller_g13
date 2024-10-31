#ifndef PEW_PEW_H
#define PEW_PEW_H
#include "weapon_interface.h"
#include "../bullets_strategy/laser.h"
#include "../bullets_strategy/bullet_interface.h"

class PewPew : public WeaponInterface {
    private:

    public:
        PewPew() { }
        std::vector<BulletInterface> fire(Position star_position, Position direction) {
            std::vector<BulletInterface> bullets;
            bullets.push_back(Laser(star_position, direction, 10));
            bullets.push_back(Laser(star_position, direction + Position(1,0), 10));
            bullets.push_back(Laser(star_position, direction + Position(-1,0), 10));
            return bullets;
        }

};

#endif