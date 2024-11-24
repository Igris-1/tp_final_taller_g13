#include "grenade.h"

#include "../../duck.h"

// std::vector<std::shared_ptr<BulletInterface>> Grenade::fire(std::shared_ptr<Duck> duck_trigger,
//                                                             int x_position, int y_position,
//                                                             int x_direction, int y_direction, bool is_holding_button) {
//     std::vector<std::shared_ptr<BulletInterface>> bullets;
//     return bullets;
// }

// int Grenade::get_id() { return GRENADE_ID; }

// int Grenade::recoil_produced() { return GRENADE_RECOIL; }

// bool Grenade::is_explosive() { return true; }

// void Grenade::activation() { this->active = true; }

// bool Grenade::is_active() { return this->active; }

// bool Grenade::exploted() { return this->explosive_time == 0; }


// void Grenade::fire_rate_down() {
//     if (!this->active) {
//         return;
//     }
//     this->explosive_time--;
// }