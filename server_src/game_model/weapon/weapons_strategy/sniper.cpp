#include "sniper.h"

#include "../../duck.h"


Sniper::Sniper(int shot, int damage, int recoil, int scope, int reload_time) : WeaponInterface(shot, damage, recoil, scope, reload_time) {}


std::vector<std::shared_ptr<BulletInterface>> Sniper::fire(std::shared_ptr<Duck> duck_trigger,
                                                            int x_position, int y_position,
                                                            int x_direction, int y_direction,
                                                            bool is_holding_button) {
    std::vector<std::shared_ptr<BulletInterface>> bullets;
    if (this->shot == 0) {
        return bullets;
    }
    if (this->reload && !is_holding_button) {
        std::cout << "Reloading sniper" << std::endl;
        this->fire_rate = this->reload_time;
        this->reload = false;
        return bullets;
    }
    if (this->fire_rate == 0 && !is_holding_button) {
        std::cout << "fire sniper" << std::endl;
        bullets.push_back(std::make_shared<Bullet>(duck_trigger->get_id(), x_position, y_position,
                                                   x_direction, y_direction,
                                                   TILE_SIZE * this->scope, this->damage, 8));
        this->shot -= bullets.size();
        this->reload = true;
    }
    return bullets;
}

int Sniper::get_id() { return SNIPER_ID; }

int Sniper::recoil_produced() {
    return this->recoil;
}
int Sniper::get_sound() {
    return 2;
}