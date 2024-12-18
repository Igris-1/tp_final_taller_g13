#include "magnum.h"

#include "../../duck.h"
#define MAGNUM_SOUND 2
#define BULLET_SIZE 8

Magnum::Magnum(int shot, int damage, int recoil, int scope, int reload_time):
        WeaponInterface(shot, damage, recoil, scope, reload_time) {}


std::vector<std::shared_ptr<BulletInterface>> Magnum::fire(std::shared_ptr<Duck> duck_trigger,
                                                           int x_position, int y_position,
                                                           int x_direction, int y_direction,
                                                           bool is_holding_button) {
    std::vector<std::shared_ptr<BulletInterface>> bullets;
    if (this->shot == 0) {
        return bullets;
    }
    if (this->fire_rate == 0 && !is_holding_button) {
        bullets.push_back(std::make_shared<Bullet>(duck_trigger->get_id(), x_position, y_position,
                                                   x_direction, y_direction,
                                                   TILE_SIZE * this->scope, this->damage, BULLET_SIZE));
        this->shot--;
        this->fire_rate = this->reload_time;
    }
    return bullets;
}

int Magnum::get_id() { return MAGNUM_ID; }

int Magnum::recoil_produced() { return this->recoil; }

int Magnum::get_sound(bool is_holding_button) {   
    if(this->shot == 0){
    return NO_WEAPON_SOUND;
    }
    if(!is_holding_button && this->fire_rate == 0){
        return MAGNUM_SOUND;
    }
    return NO_WEAPON_SOUND;
}