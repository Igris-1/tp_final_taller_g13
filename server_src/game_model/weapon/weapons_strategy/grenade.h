#ifndef GRENADE_H
#define GRENADE_H

#include "../bullets_strategy/bullet_interface.h"

#include "weapon_interface.h"

// class Grenade: public WeaponInterface {
// private:
//     bool active = false;
//     int explosive_time = FIRE_RATE_GRENADE;

// public:
//     std::vector<std::shared_ptr<BulletInterface>> fire(std::shared_ptr<Duck> duck_trigger,
//                                                        int x_position, int y_position,
//                                                        int x_direction, int y_direction, bool is_holding_button) override;
//     int get_id() override;
//     int recoil_produced() override;
//     bool is_explosive() override;
//     bool is_active() override;
//     void activation() override;
//     bool exploted() override;
//     void fire_rate_down() override;
//     ~Grenade() override {}
// };

#endif
