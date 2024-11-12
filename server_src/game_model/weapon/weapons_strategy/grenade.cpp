#include "grenade.h"
#include "../../duck.h"

std::vector<std::shared_ptr<BulletInterface>> Grenade::fire(std::shared_ptr<Duck> duck_trigger, int x_position, int y_position, int x_direction, int y_direction){
    std::vector<std::shared_ptr<BulletInterface>> bullets;
    return bullets;
}

int Grenade::get_id(){
    return 2;
}

int Grenade::recoil_produced(){
    return 0;
}

bool  Grenade::is_explosive(){
    return true;
}

void Grenade::activation_time(){
    this->is_active = true;
}

void  Grenade::fire_rate_down(){
    if(this->is_active == false){
        return;
    }
    this->fire_rate --;
}