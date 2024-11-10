#ifndef COWBOY_PISTOL_H
#define COWBOY_PISTOL_H

#include "weapon_interface.h"
#include "../bullets_strategy/bullet.h"
#include "../bullets_strategy/bullet_interface.h"

#define FIRE_RATE_COWBOY 20

class CowboyPistol : public WeaponInterface{
    private:
      int ammo = 600; 
    public:
         std::vector<std::shared_ptr<BulletInterface>> fire(int x_position, int y_position, int x_direction, int y_direction, int dispersion) override {
            std::vector<std::shared_ptr<BulletInterface>>  bullets;
            if(ammo == 0){
               return bullets;
            }
            if(fire_rate == 0){
               bullets.push_back(std::make_shared<Bullet>(x_position, y_position, x_direction, y_direction));
               ammo--;
               this->fire_rate = FIRE_RATE_COWBOY;
            }
            return bullets;
         }
         ~CowboyPistol() override {}
};

#endif