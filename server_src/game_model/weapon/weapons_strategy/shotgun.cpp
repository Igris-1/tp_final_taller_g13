#include "shotgun.h"

#include "../../duck.h"

std::vector<std::shared_ptr<BulletInterface>> Shotgun::fire(std::shared_ptr<Duck> duck_trigger,
                                                            int x_position, int y_position,
                                                            int x_direction, int y_direction,
                                                            bool is_holding_button) {
    std::vector<std::shared_ptr<BulletInterface>> bullets;
    if (this->ammo == 0) {
        return bullets;
    }
    if (this->reload && !is_holding_button) {
        std::cout << "Reloading shotgun" << std::endl;
        this->fire_rate = FIRE_RATE_SHOTGUN;
        this->reload = false;
        return bullets;
    }
    if (this->fire_rate == 0 && !is_holding_button) {
        std::cout << "fire shotgun" << std::endl;
        bullets.push_back(std::make_shared<Pellet>(duck_trigger->get_id(), x_position, y_position,
                                                   x_direction, y_direction,
                                                   TRAVEL_DISTANCE_SHOTGUN));
        bullets.push_back(std::make_shared<Pellet>(duck_trigger->get_id(), x_position,
                                                   y_position - 1, x_direction, y_direction,
                                                   TRAVEL_DISTANCE_SHOTGUN));

        bullets.push_back(std::make_shared<Pellet>(duck_trigger->get_id(), x_position,
                                                   y_position + 1, x_direction, y_direction + 1,
                                                   TRAVEL_DISTANCE_SHOTGUN));

        bullets.push_back(std::make_shared<Pellet>(duck_trigger->get_id(), x_position,
                                                   y_position - 1, x_direction, y_direction - 1,
                                                   TRAVEL_DISTANCE_SHOTGUN));

        bullets.push_back(std::make_shared<Pellet>(duck_trigger->get_id(), x_position,
                                                   y_position - 2, x_direction, y_direction - 2,
                                                   TRAVEL_DISTANCE_SHOTGUN));

        bullets.push_back(std::make_shared<Pellet>(duck_trigger->get_id(), x_position,
                                                   y_position + 2, x_direction, y_direction + 2,
                                                   TRAVEL_DISTANCE_SHOTGUN));
        ammo -= bullets.size();
        this->reload = true;
    }
    return bullets;
}

int Shotgun::get_id() { return SHOTGUN_ID; }

int Shotgun::recoil_produced() {
    if (this->fire_rate > 0 && !this->reload){
        return SHOTGUN_RECOIL;
    }
    return 0;
}