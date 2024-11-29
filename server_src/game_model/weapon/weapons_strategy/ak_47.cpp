#include "ak_47.h"

#include "../../duck.h"

AK47::AK47(int shot, int damage, int recoil, int scope, int reload_time):
        WeaponInterface(shot, damage, recoil, scope, reload_time) {}

std::vector<std::shared_ptr<BulletInterface>> AK47::fire(std::shared_ptr<Duck> duck_trigger,
                                                         int x_position, int y_position,
                                                         int x_direction, int y_direction,
                                                         bool is_holding_button) {
    std::vector<std::shared_ptr<BulletInterface>> bullets;
    if (this->shot == 0) {
        std::cout << "No ammo" << std::endl;
        return bullets;
    }
    if (this->fire_rate == 0) {
        std::cout << "fire AK47" << std::endl;
        bullets.push_back(std::make_shared<Bullet>(duck_trigger->get_id(), x_position, y_position,
                                                   x_direction, y_direction,
                                                   TILE_SIZE * this->scope, this->damage, 8));
        this->shot--;
        this->fire_rate = this->reload_time;
    }
    return bullets;
}

int AK47::get_id() { return AK_47_ID; }

int AK47::get_sound() { return 2; }

int AK47::recoil_produced() { return this->recoil; }