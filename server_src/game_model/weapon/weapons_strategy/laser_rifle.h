#ifndef LASER_RIFLE_H
#define LASER_RIFLE_H

#include "weapon_interface.h"
#include "../bullets_strategy/laser.h"

#define FIRE_RATE_LASER 5

class LaserRifle : public WeaponInterface {

    private:
      int ammo = 1000000;//DAME BALAS ESTOY TRESTESANDO COASAS LA CONCHA D TU AMDRE
    public:
      std::vector<std::shared_ptr<BulletInterface>> fire(int x_position, int y_position, int x_direction, int y_direction, int dispersion) override {
         std::vector<std::shared_ptr<BulletInterface>> bullets;
         if(ammo == 0){
            return bullets;
         }
         if(fire_rate == 0){
            bullets.push_back(std::make_shared<Laser>(x_position, y_position, x_direction, y_direction));
            ammo--;
            this->fire_rate = FIRE_RATE_LASER;
         }
         return bullets;
      }
      
      ~LaserRifle() override {}
};

#endif
