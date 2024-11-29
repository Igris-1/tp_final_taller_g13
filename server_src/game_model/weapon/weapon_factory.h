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
#include "weapons_strategy/magnum.h"
#include "weapons_strategy/dueling_pistol.h"

#include "../../../configuration_yamls/game_config.h"

class Pickable;

class WeaponFactory {
public:
    // "cowboy", "sniper", "shotgun", "pew_pew", "laser_rifle", "" (no weapon)
    static std::shared_ptr<Pickable> createWeapon(std::list<std::shared_ptr<BulletInterface>>& bullets,
                               std::string weapon_name, const std::map<std::string, weapon_config>& weapons_config);
};

#endif  // WEAPON_FACTORY_H