#ifndef SHOTGUN_H
#define SHOTGUN_H

#include <memory>

#include "../bullets_strategy/bullet_interface.h"
#include "../bullets_strategy/pellet.h"

#include "weapon.h"
#include "weapon_interface.h"

#define SIMPLE_DISPERSION 1
#define DOUBLE_DISPERSION 2
#define SHOTGUN_SOUND 2

class Shotgun: public WeaponInterface {
private:
    bool reload = false;

    std::vector<std::shared_ptr<BulletInterface>> create_shot(int id_duck,
                int x_position, int y_position, int x_direction, int y_direction, bool vertical);
public:
    Shotgun(int shot, int damage, int recoil, int scope, int reload_time);
    std::vector<std::shared_ptr<BulletInterface>> fire(std::shared_ptr<Duck> duck_trigger,
                                                       int x_position, int y_position,
                                                       int x_direction, int y_direction,
                                                       bool is_holding_button) override;
    int get_id() override;
    int recoil_produced() override;
    int get_sound() override;
    ~Shotgun() override {}
};

#endif
