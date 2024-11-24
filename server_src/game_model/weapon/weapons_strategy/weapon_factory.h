#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include <string>

#include "cowboy_pistol.h"
#include "laser_rifle.h"
#include "pew_pew.h"
#include "shotgun.h"
#include "sniper.h"
#include "ak_47.h"
#include <cstdlib>
#include <ctime>
#include <list>

class Weapon;

class WeaponFactory {
public:
    // "cowboy", "sniper", "shotgun", "pew_pew", "laser_rifle", "" (no weapon)
    static Weapon createWeapon(std::list<std::shared_ptr<BulletInterface>>& bullets,
                               std::string weapon_name = "");
};

#endif  // WEAPON_FACTORY_H