#include "weapon_interface.h"

WeaponInterface::WeaponInterface(int shot, int damage, int recoil, int scope, int reload_time):
        shot(shot), damage(damage), recoil(recoil), scope(scope), reload_time(reload_time) {}

void WeaponInterface::fire_rate_down() {
    if (this->fire_rate > 0) {
        this->fire_rate--;
    }
}

int WeaponInterface::get_sound(bool is_holding_button) { return NO_SOUND; }
