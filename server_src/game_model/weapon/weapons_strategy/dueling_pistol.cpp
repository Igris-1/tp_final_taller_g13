#include "dueling_pistol.h"
#include "../../duck.h"

#define DUELING_PISTOL_SOUND 2

DuelingPistol::DuelingPistol(int shot, int damage, int recoil, int scope, int reload_time):
        WeaponInterface(shot, damage, recoil, scope, reload_time) {}


std::vector<std::shared_ptr<BulletInterface>> DuelingPistol::fire(
        std::shared_ptr<Duck> duck_trigger, int x_position, int y_position, int x_direction,
        int y_direction, bool is_holding_button) {
    std::vector<std::shared_ptr<BulletInterface>> bullets;
    if (this->shot == 0) {
        return bullets;
    }
    if (this->fire_rate == 0 && !is_holding_button) {
        bullets.push_back(std::make_shared<Bullet>(duck_trigger->get_id(), x_position, y_position,
                                                   x_direction, y_direction,
                                                   TILE_SIZE * this->scope, this->damage, 8));
        this->shot--;
        this->fire_rate = this->reload_time;
    }
    return bullets;
}

int DuelingPistol::get_id() { return DUELING_PISTOL_ID; }

int DuelingPistol::recoil_produced() { return this->recoil; }

int DuelingPistol::get_sound(bool is_holding_button) { 
    if(this->shot == 0){
        return NO_WEAPON_SOUND;
    }
    if(!is_holding_button && this->fire_rate == 0){
        return DUELING_PISTOL_SOUND;
    }
    return NO_WEAPON_SOUND; 
}