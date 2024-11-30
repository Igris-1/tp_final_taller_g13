#include "pew_pew.h"

#include "../../duck.h"

#define LASER_PER_SHOT 3
#define LASER_SIZE 8
#define PEW_PEW_SOUND 3

PewPew::PewPew(int shot, int damage, int recoil, int scope, int reload_time):
        WeaponInterface(LASER_PER_SHOT * shot, damage, recoil, scope, reload_time) {}

std::vector<std::shared_ptr<BulletInterface>> PewPew::fire(std::shared_ptr<Duck> duck_trigger,
                                                           int x_position, int y_position,
                                                           int x_direction, int y_direction,
                                                           bool is_holding_button) {

    std::vector<std::shared_ptr<BulletInterface>> bullets;
    if (this->shot == 0) {
        return bullets;
    }
    if (this->fire_rate == 0) {
        bullets.push_back(std::make_shared<Laser>(duck_trigger->get_id(), x_position, y_position,
                                                  x_direction, DOWN_DISPERSION, TILE_SIZE * this->scope,
                                                  this->damage, LASER_SIZE));
        bullets.push_back(std::make_shared<Laser>(duck_trigger->get_id(), x_position, y_position,
                                                  x_direction, NO_DISPERSION, TILE_SIZE * this->scope,
                                                  this->damage, LASER_SIZE));
        bullets.push_back(std::make_shared<Laser>(duck_trigger->get_id(), x_position, y_position,
                                                  x_direction, UP_DISPERSION, TILE_SIZE * this->scope,
                                                  this->damage, LASER_SIZE));
        ;

        this->shot--;
        this->fire_rate = this->reload_time;
    }
    return bullets;
}

int PewPew::get_id() { return PEW_PEW_LASER_ID; }
int PewPew::recoil_produced() { return this->recoil; }
int PewPew::get_sound(bool is_holding_button) {  
    if(this->shot == 0){
    return NO_WEAPON_SOUND;
    }
    return PEW_PEW_SOUND;
}
