#ifndef AK_47_H
#define AK_47_H

#include <memory>

#include "../bullets_strategy/bullet.h"
#include "../bullets_strategy/bullet_interface.h"
#include "weapon.h"

#include "weapon_interface.h"


class AK47: public WeaponInterface {
private:
    int ammo = 99999;

public:
    std::vector<std::shared_ptr<BulletInterface>> fire(std::shared_ptr<Duck> duck_trigger,
                                                       int x_position, int y_position,
                                                       int x_direction, int y_direction, bool is_holding_button) override;
    int get_id() override;
    int recoil_produced() override;
    ~AK47() override {}
};

#endif