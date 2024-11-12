#ifndef GRENADE_H
#define GRENADE_H

#include "weapon_interface.h"
#include "../bullets_strategy/bullet_interface.h"

class Grenade : public WeaponInterface {
    private:
        bool is_active = false;
        int time_to_explote = 1000;
    public:
        std::vector<std::shared_ptr<BulletInterface>> fire(std::shared_ptr<Duck> duck_trigger, int x_position, int y_position, int x_direction, int y_direction) override;
        int get_id() override;
        int recoil_produced() override;
        bool is_explosive() override;
        void activation_time();
        void fire_rate_down() override;
        ~Grenade() override {}
};

#endif
