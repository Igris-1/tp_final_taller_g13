#include "shotgun.h"

#include "../../duck.h"

#define PELLETS_PER_SHOT 6
#define SIZE_OF_PELLET 8

Shotgun::Shotgun(int shot, int damage, int recoil, int scope, int reload_time):
        WeaponInterface(PELLETS_PER_SHOT * shot, damage, recoil, scope, reload_time) {}

std::vector<std::shared_ptr<BulletInterface>> Shotgun::create_shot(int id_duck,
                                                            int x_position, int y_position, int x_direction, 
                                                            int y_direction, bool vertical){ 
    std::vector<std::shared_ptr<BulletInterface>> bullets;
    const int dispersions[] = {0, 0, SIMPLE_DISPERSION, -SIMPLE_DISPERSION, DOUBLE_DISPERSION, -DOUBLE_DISPERSION};

    for (int i = 0; i < (sizeof(dispersions) / sizeof(dispersions[0])); i++) {
        int dx = (vertical) ? dispersions[i] : 0;
        int dy = (vertical) ? 0 : dispersions[i];

        bullets.push_back(std::make_shared<Pellet>( id_duck, x_position + dx, y_position + dy, 
                        x_direction + dx, y_direction + dy, TILE_SIZE * this->scope, this->damage,
                         SIZE_OF_PELLET, vertical));
    }
    return bullets;
} 

std::vector<std::shared_ptr<BulletInterface>> Shotgun::fire(std::shared_ptr<Duck> duck_trigger,
                                                            int x_position, int y_position,
                                                            int x_direction, int y_direction,
                                                            bool is_holding_button) {
    std::vector<std::shared_ptr<BulletInterface>> bullets;
    if (this->shot == 0) {
        return bullets;
    }
    if (this->reload && !is_holding_button) {
        this->fire_rate = this->reload_time;
        this->reload = false;
        return bullets;
    }
    bool vertical = true;
    if (this->fire_rate == 0 && !is_holding_button) {
        if(x_direction * x_direction > y_direction * y_direction){ 
            vertical = false;
         }
        bullets = create_shot(duck_trigger->get_id(), x_position, y_position, 
                    x_direction, y_direction, vertical);
        this->shot -= bullets.size();
        this->reload = true;
    }
    return bullets;
}

int Shotgun::get_id() { return SHOTGUN_ID; }

int Shotgun::recoil_produced() { return this->recoil; }

int Shotgun::get_sound(bool is_holding_button) { 
    
    if(this->shot == 0){
        std::cout << "sin balas" << std::endl;
        return NO_WEAPON_SOUND;
    }
    if(this->reload && !is_holding_button){
        std::cout << "recargando" << std::endl;
        return SHOTGUN_RECHARGING_SOUND;
    }
    if(!is_holding_button && this->fire_rate == 0){
        std::cout << "disparando" << std::endl;
        return SHOTGUN_SOUND; 
    }
    std::cout << "no sound" << std::endl;
    return NO_WEAPON_SOUND;
}