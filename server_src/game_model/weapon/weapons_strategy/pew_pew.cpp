#include "pew_pew.h"
#include "../../duck.h"
PewPew::PewPew() {}

std::vector<std::shared_ptr<BulletInterface>> PewPew::fire(std::shared_ptr<Duck> duck_trigger,
                                                               int x_position, int y_position,
                                                               int x_direction, int y_direction,
                                                               bool is_holding_button) {
                            
    std::vector<std::shared_ptr<BulletInterface>> bullets;
    if (this->ammo == 0) {
        return bullets;
    }
    if (this->fire_rate == 0) {
        bullets.push_back(std::make_shared<Laser>(duck_trigger->get_id(), x_position, y_position,
                                                  x_direction, 1, TRAVEL_DISTANCE_PEW_PEW));
        bullets.push_back(std::make_shared<Laser>(duck_trigger->get_id(), x_position, y_position,
                                                  x_direction, 0, TRAVEL_DISTANCE_PEW_PEW));
        bullets.push_back(std::make_shared<Laser>(duck_trigger->get_id(), x_position, y_position,
                                                  x_direction, -1, TRAVEL_DISTANCE_PEW_PEW));
        
        ammo--;
        this->fire_rate = FIRE_RATE_PEW_PEW;
    }
    return bullets;
}

int PewPew::get_id(){
    return PEW_PEW_LASER_ID;
}
int PewPew::recoil_produced(){
        return 0;
}

