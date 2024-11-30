#ifndef SNIPER_H
#define SNIPER_H

#include <memory>

#include "../bullets_strategy/fmj_bullet.h"
#include "../bullets_strategy/bullet_interface.h"

#include "weapon.h"
#include "weapon_interface.h"

#define SNIPER_SOUND 2
#define SNIPER_RECHARGING_SOUND 5

class Sniper: public WeaponInterface {
private:
    bool reload = false;

public:
    Sniper(int shot, int damage, int recoil, int scope, int reload_time);
    std::vector<std::shared_ptr<BulletInterface>> fire(std::shared_ptr<Duck> duck_trigger,
                                                       int x_position, int y_position,
                                                       int x_direction, int y_direction,
                                                       bool is_holding_button) override;
    int get_id() override;
    int recoil_produced() override;
    int get_sound(bool is_holding_button) override;
    ~Sniper() override {}
};

#endif
