#ifndef LASER_RIFLE_H
#define LASER_RIFLE_H

#include "../bullets_strategy/bullet_interface.h"
#include "../bullets_strategy/laser.h"

#include "weapon.h"
#include "weapon_interface.h"


class LaserRifle: public WeaponInterface {

private:
public:
    LaserRifle(int shot, int damage, int recoil, int scope, int reload_time);
    std::vector<std::shared_ptr<BulletInterface>> fire(std::shared_ptr<Duck> duck_trigger,
                                                       int x_position, int y_position,
                                                       int x_direction, int y_direction,
                                                       bool is_holding_button) override;
    int get_id() override;
    int recoil_produced() override;
    int get_sound(bool is_holding_button) override;
    ~LaserRifle() override {}
};

#endif
