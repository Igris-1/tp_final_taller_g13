#ifndef LASER_RIFLE_H
#define LASER_RIFLE_H

#include "weapon_interface.h"
#include "../bullets_strategy/laser.h"
#include "../bullets_strategy/bullet_interface.h"


class LaserRifle : public WeaponInterface {

    private:
      int ammo = 1000000;//DAME BALAS ESTOY TRESTESANDO COASAS LA CONCHA D TU AMDRE
    public:
      std::vector<std::shared_ptr<BulletInterface>> fire(std::shared_ptr<Duck> duck_trigger, int x_position, int y_position, int x_direction, int y_direction) override;
      int get_id() override;
      int recoil_produced() override;
      ~LaserRifle() override {}
};

#endif
