#include "ak_47.h"
#include "../../duck.h"

std::vector<std::shared_ptr<BulletInterface>> AK47::fire(std::shared_ptr<Duck> duck_trigger,
                                                                 int x_position, int y_position,
                                                                 int x_direction, int y_direction, bool is_holding_button) {
    std::vector<std::shared_ptr<BulletInterface>> bullets;
    if (this->ammo == 0) {
        return bullets;
    }
    if (this->fire_rate == 0) {
        bullets.push_back(std::make_shared<Bullet>(duck_trigger->get_id(), x_position, y_position,
                                                   x_direction, y_direction, TRAVEL_DISTANCE_AK47));
        ammo--;
        this->fire_rate = FIRE_RATE_AK47;
    }
    return bullets;
}

int AK47::get_id() { return AK_47_ID; }

int AK47::recoil_produced() { return AK47_RECOIL; }