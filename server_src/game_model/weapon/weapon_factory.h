#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include <cstdlib>
#include <ctime>
#include <list>
#include <string>
#include <memory>

#include "weapons_strategy/ak_47.h"
#include "weapons_strategy/cowboy_pistol.h"
#include "weapons_strategy/laser_rifle.h"
#include "weapons_strategy/pew_pew.h"
#include "weapons_strategy/shotgun.h"
#include "weapons_strategy/sniper.h"
#include "../pickable.h"

class Weapon;

class WeaponFactory {
public:
    // "cowboy", "sniper", "shotgun", "pew_pew", "laser_rifle", "" (no weapon)
    static std::shared_ptr<Pickable> createWeapon(std::list<std::shared_ptr<BulletInterface>>& bullets,
                               std::string weapon_name);
};

#endif  // WEAPON_FACTORY_H