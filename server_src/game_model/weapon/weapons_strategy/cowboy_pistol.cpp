#include "cowboy_pistol.h"

#include "../../duck.h"
#define COWBOY_PISTOL_SOUND 1
#define BULLET_SIZE 8

CowboyPistol::CowboyPistol(int shot, int damage, int recoil, int scope, int reload_time):
        WeaponInterface(shot, damage, recoil, scope, reload_time) {}


std::vector<std::shared_ptr<BulletInterface>> CowboyPistol::fire(std::shared_ptr<Duck> duck_trigger,
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

int CowboyPistol::get_id() { return COWBOY_PISTOL_ID; }

int CowboyPistol::recoil_produced() { return this->recoil; }

int CowboyPistol::get_sound(bool is_holding_button) {   
    if(this->shot == 0){
        return NO_WEAPON_SOUND;
    }
    if(!is_holding_button && this->fire_rate == 0){
        return COWBOY_PISTOL_SOUND;
    }
    return NO_WEAPON_SOUND;
 }