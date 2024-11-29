#include "shotgun.h"

#include "../../duck.h"

#define PELLETS_PER_SHOT 6
#define SIZE_OF_PELLET 8

Shotgun::Shotgun(int shot, int damage, int recoil, int scope, int reload_time):
        WeaponInterface(PELLETS_PER_SHOT * shot, damage, recoil, scope, reload_time) {}


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
    if (this->fire_rate == 0 && !is_holding_button) {
        if(x_direction * x_direction > y_direction * y_direction){ 
            // pq ^2? pq necesito ver si el valor abs es mayor. 
            // mas facil q importar una biblioteca de matematica
 
            bullets.push_back(std::make_shared<Pellet>(duck_trigger->get_id(), x_position, y_position,
                                                   x_direction, y_direction,
                                                   TILE_SIZE * this->scope, this->damage, SIZE_OF_PELLET, false));
            bullets.push_back(std::make_shared<Pellet>(duck_trigger->get_id(), x_position,
                                                   y_position - 1, x_direction, y_direction,
                                                   TILE_SIZE * this->scope, this->damage, SIZE_OF_PELLET, false));

            bullets.push_back(std::make_shared<Pellet>(duck_trigger->get_id(), x_position,
                                                   y_position + 1, x_direction, y_direction + 1,
                                                   TILE_SIZE * this->scope, this->damage, SIZE_OF_PELLET, false));

            bullets.push_back(std::make_shared<Pellet>(duck_trigger->get_id(), x_position,
                                                   y_position - 1, x_direction, y_direction - 1,
                                                   TILE_SIZE * this->scope, this->damage, SIZE_OF_PELLET, false));

            bullets.push_back(std::make_shared<Pellet>(duck_trigger->get_id(), x_position,
                                                   y_position - 2, x_direction, y_direction - 2,
                                                   TILE_SIZE * this->scope, this->damage, SIZE_OF_PELLET, false));

            bullets.push_back(std::make_shared<Pellet>(duck_trigger->get_id(), x_position,
                                                   y_position + 2, x_direction, y_direction + 2,
                                                   TILE_SIZE * this->scope, this->damage, SIZE_OF_PELLET, false));
        }else{
            bullets.push_back(std::make_shared<Pellet>(duck_trigger->get_id(), x_position, y_position,
                                                   x_direction, y_direction,
                                                   TILE_SIZE * this->scope, this->damage, SIZE_OF_PELLET, true));
            bullets.push_back(std::make_shared<Pellet>(duck_trigger->get_id(), x_position - 1,
                                                   y_position, x_direction, y_direction,
                                                   TILE_SIZE * this->scope, this->damage, SIZE_OF_PELLET, true));

            bullets.push_back(std::make_shared<Pellet>(duck_trigger->get_id(), x_position + 1,
                                                   y_position, x_direction + 1, y_direction,
                                                   TILE_SIZE * this->scope, this->damage, SIZE_OF_PELLET, true));

            bullets.push_back(std::make_shared<Pellet>(duck_trigger->get_id(), x_position  - 1,
                                                   y_position, x_direction  - 1, y_direction,
                                                   TILE_SIZE * this->scope, this->damage, SIZE_OF_PELLET, true));

            bullets.push_back(std::make_shared<Pellet>(duck_trigger->get_id(), x_position  - 2,
                                                   y_position, x_direction  - 2, y_direction,
                                                   TILE_SIZE * this->scope, this->damage, SIZE_OF_PELLET, true));

            bullets.push_back(std::make_shared<Pellet>(duck_trigger->get_id(), x_position + 2,
                                                   y_position, x_direction + 2, y_direction,
                                                   TILE_SIZE * this->scope, this->damage, SIZE_OF_PELLET, true));
        }
        
        this->shot -= bullets.size();
        this->reload = true;
    }
    return bullets;
}

int Shotgun::get_id() { return SHOTGUN_ID; }

int Shotgun::recoil_produced() { return this->recoil; }

int Shotgun::get_sound() { return 2; }