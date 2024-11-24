#ifndef SHOTGUN_H
#define SHOTGUN_H

#include <memory>

#include "../bullets_strategy/bullet_interface.h"
#include "../bullets_strategy/pellet.h"

#include "weapon.h"
#include "weapon_interface.h"


class Shotgun: public WeaponInterface {
private:
    int ammo = 12;
    bool reload = false;

public:
    std::vector<std::shared_ptr<BulletInterface>> fire(std::shared_ptr<Duck> duck_trigger,
                                                       int x_position, int y_position,
                                                       int x_direction, int y_direction,
                                                       bool is_holding_button) override;
    int get_id() override;
    int recoil_produced() override;
    ~Shotgun() override {}
};

#endif
