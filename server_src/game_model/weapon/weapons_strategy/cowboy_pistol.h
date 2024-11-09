#ifndef COWBOY_PISTOL_H
#define COWBOY_PISTOL_H

#include "weapon_interface.h"
#include "../bullets_strategy/bullet.h"
#include "../bullets_strategy/bullet_interface.h"

#define TILES_PELLET_DISTANCE 300

class CowboyPistol : public WeaponInterface{
    private:
      int ammo = 6;

    public:
         std::vector<BulletInterface> fire(int x_position, int y_position, int x_direction, int y_direction, int dispersion) override {
            std::vector<BulletInterface> bullets;
            if(ammo == 0){
               return bullets;
            }
            bullets.push_back(Bullet(x_position, y_position, x_direction, y_direction));
            ammo--;
            return bullets;
         }

         ~CowboyPistol() override {}
};

#endif