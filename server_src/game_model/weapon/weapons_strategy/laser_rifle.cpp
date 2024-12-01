#include "laser_rifle.h"

#include "../../duck.h"
#define LASER_RIFLE_SOUND 3
#define DISPERSION_LASER_RIFLE 1
#define LASER_SIZE 8

LaserRifle::LaserRifle(int shot, int damage, int recoil, int scope, int reload_time):
        WeaponInterface(shot, damage, recoil, scope, reload_time) {}


std::vector<std::shared_ptr<BulletInterface>> LaserRifle::fire(std::shared_ptr<Duck> duck_trigger,
                                                               int x_position, int y_position,
                                                               int x_direction, int y_direction,
                                                               bool is_holding_button) {
    std::vector<std::shared_ptr<BulletInterface>> bullets;
    if (this->shot == 0) {
        return bullets;
    }
    if (this->fire_rate == 0) {
        bullets.push_back(std::make_shared<Laser>(duck_trigger->get_id(), x_position, y_position,
                                                  x_direction, DISPERSION_LASER_RIFLE, TILE_SIZE * this->scope,
                                                  this->damage, LASER_SIZE));
        this->shot--;
        this->fire_rate = this->reload_time;
    }
    return bullets;
}

int LaserRifle::get_id() { return LASER_RIFLE_ID; }

int LaserRifle::recoil_produced() { return this->recoil; }

int LaserRifle::get_sound(bool is_holding_button) { 
    if(this->shot == 0){
        return NO_WEAPON_SOUND;
    }
    if(this->fire_rate == 0){
        return LASER_RIFLE_SOUND;
    }
    return NO_WEAPON_SOUND;
}