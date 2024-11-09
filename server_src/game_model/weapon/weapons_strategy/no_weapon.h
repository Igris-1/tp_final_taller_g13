#ifndef NO_WEAPON_H
#define NO_WEAPON_H

#include "../bullets_strategy/bullet_interface.h"
#include "../../positionable.h"
#include "weapon_interface.h"
#include <vector>

class NoWeapon : public WeaponInterface {

    public:
        NoWeapon(){};
        std::vector<BulletInterface> fire(int x_position, int y_position, int x_direction, int y_direction, int dispersion) override {
            return std::vector<BulletInterface>();
        }
        bool no_real(){
            return false;
        }
        ~NoWeapon() override {}
}; 

#endif