#ifndef COWBOY_PISTOL_H
#define COWBOY_PISTOL_H

#include <memory>

#include "../bullets_strategy/bullet.h"
#include "../bullets_strategy/bullet_interface.h"
#include "weapon.h"

#include "weapon_interface.h"


class CowboyPistol: public WeaponInterface {
private:
    int ammo = 6;

public:
    std::vector<std::shared_ptr<BulletInterface>> fire(std::shared_ptr<Duck> duck_trigger,
                                                       int x_position, int y_position,
                                                       int x_direction, int y_direction, bool is_holding_button) override;
    int get_id() override;
    int recoil_produced() override;
    ~CowboyPistol() override {}
};

#endif