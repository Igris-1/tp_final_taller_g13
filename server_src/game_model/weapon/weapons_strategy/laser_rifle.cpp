#include "laser_rifle.h"

#include "../../duck.h"

std::vector<std::shared_ptr<BulletInterface>> LaserRifle::fire(std::shared_ptr<Duck> duck_trigger,
                                                               int x_position, int y_position,
                                                               int x_direction, int y_direction, bool is_holding_button) {
    std::vector<std::shared_ptr<BulletInterface>> bullets;
    if (this->ammo == 0) {
        return bullets;
    }
    if (this->fire_rate == 0) {
        bullets.push_back(std::make_shared<Laser>(duck_trigger->get_id(), x_position, y_position,
                                                  x_direction, 1, TRAVEL_DISTANCE_LASER_RIFLE));
        ammo--;
        this->fire_rate = FIRE_RATE_LASER_RIFLE;
    }
    return bullets;
}

int LaserRifle::get_id() { return LASER_RIFLE_ID; }

int LaserRifle::recoil_produced() { return LASER_RIFLE_RECOIL; }