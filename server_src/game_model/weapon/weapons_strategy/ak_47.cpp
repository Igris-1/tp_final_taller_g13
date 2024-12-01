#include "ak_47.h"

#include "../../duck.h"


#define BULLET_SIZE 8
#define AK47_SOUND 2

#define NO_DISPERSION 0
#define POSITIVE_DISPERSION 5
#define NEGATIVE_DISPERSION -15
#define Y_DISPERSION 1

AK47::AK47(int shot, int damage, int recoil, int scope, int reload_time):
        WeaponInterface(shot, damage, recoil, scope, reload_time) {}

std::vector<std::shared_ptr<BulletInterface>> AK47::fire(std::shared_ptr<Duck> duck_trigger,
                                                         int x_position, int y_position,
                                                         int x_direction, int y_direction,
                                                         bool is_holding_button) {
    std::vector<std::shared_ptr<BulletInterface>> bullets;
    if (this->shot == 0) {
        return bullets;
    }
    if (this->fire_rate == 0) {
        if(!is_holding_button){
            this->dispersion = 0;
        }
        bullets.push_back(std::make_shared<Bullet>( duck_trigger->get_id(), x_position, y_position + this->dispersion, 
                        x_direction , y_direction+dispersion2, TILE_SIZE * this->scope, this->damage,
                        BULLET_SIZE));
        switch (this->dispersion) {
            case NO_DISPERSION:
                this->dispersion = POSITIVE_DISPERSION;
                this->dispersion2 = NO_DISPERSION;
                break;
            case POSITIVE_DISPERSION:
                this->dispersion = NEGATIVE_DISPERSION;
                break;
            case NEGATIVE_DISPERSION:
                this->dispersion = Y_DISPERSION;
                break;
            case Y_DISPERSION:
                this->dispersion = NO_DISPERSION;
                this->dispersion2 = - Y_DISPERSION;
                break;
        }
        this->shot--;
        this->fire_rate = this->reload_time;
    }
    return bullets;
}

int AK47::get_id() { return AK_47_ID; }

int AK47::get_sound(bool is_holding_button) {   
    if(this->shot == 0){
        return NO_WEAPON_SOUND;
    }
    if(this->fire_rate == 0){
        return AK47_SOUND;
    }
    return NO_WEAPON_SOUND;

 }

int AK47::recoil_produced() { return this->recoil; }