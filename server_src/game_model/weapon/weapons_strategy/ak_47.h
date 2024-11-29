#ifndef AK_47_H
#define AK_47_H

#include <memory>

#include "../bullets_strategy/bullet.h"
#include "../bullets_strategy/bullet_interface.h"

#include "weapon.h"
#include "weapon_interface.h"


class AK47: public WeaponInterface {
private:
public:
    AK47(int shot, int damage, int recoil, int scope, int reload_time);
    std::vector<std::shared_ptr<BulletInterface>> fire(std::shared_ptr<Duck> duck_trigger,
                                                       int x_position, int y_position,
                                                       int x_direction, int y_direction,
                                                       bool is_holding_button) override;
    int get_id() override;
    int recoil_produced() override;
    int get_sound() override;
    ~AK47() override {}
};

#endif