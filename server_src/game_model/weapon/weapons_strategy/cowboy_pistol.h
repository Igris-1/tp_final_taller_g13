#ifndef COWBOY_PISTOL_H
#define COWBOY_PISTOL_H

#include "weapon_interface.h"
#include "../bullets_strategy/bullet.h"
#include "../bullets_strategy/bullet_interface.h"
#include <memory>

#define FIRE_RATE_COWBOY 20
#define COWBOY_PISTOL_ID 1

class CowboyPistol : public WeaponInterface{
    private:
      int ammo = 600; 
    public:
      std::vector<std::shared_ptr<BulletInterface>> fire(std::shared_ptr<Duck> duck_trigger, int x_position, int y_position, int x_direction, int y_direction) override;
      int get_id() override;
      int recoil_produced() override;
      ~CowboyPistol() override {}
};

#endif