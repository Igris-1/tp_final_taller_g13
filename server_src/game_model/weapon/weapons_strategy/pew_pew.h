#ifndef PEW_PEW_H
#define PEW_PEW_H
#include "../bullets_strategy/bullet_interface.h"
#include "../bullets_strategy/laser.h"

#include "weapon.h"
#include "weapon_interface.h"

#define DOWN_DISPERSION 1
#define UP_DISPERSION -1
#define NO_DISPERSION 0

class PewPew: public WeaponInterface {
private:
public:
    PewPew(int shot, int damage, int recoil, int scope, int reload_time);
    std::vector<std::shared_ptr<BulletInterface>> fire(std::shared_ptr<Duck> duck_trigger,
                                                       int x_position, int y_position,
                                                       int x_direction, int y_direction,
                                                       bool is_holding_button) override;
    int get_id() override;
    int recoil_produced() override;
    int get_sound(bool is_holding_button) override;
    ~PewPew() override{};
};

#endif