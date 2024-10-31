#ifndef WEAPON_INTERFACE_H
#define WEAPON_INTERFACE_H

#include "../bullets_strategy/bullet_interface.h"
#include "../../position.h"
#include "../../positionable.h"
#include <vector>

class WeaponInterface {
    private:

    public:
        virtual std::vector<BulletInterface> fire(Position star_position, Position direction);
};

#endif
