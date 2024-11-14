#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include <string>
#include "weapon.h"
#include "cowboy_pistol.h"
#include "shotgun.h"
#include "sniper.h"
#include "pew_pew.h"
#include "laser_rifle.h"


class WeaponFactory {
    public:
        // "cowboy", "sniper", "shotgun", "pew_pew", "laser_rifle", "" (no weapon)
        static Weapon createWeapon(std::list<std::shared_ptr<BulletInterface>>& bullets, std::string weapon_name = ""){
            if (weapon_name == "cowboy") {
                return Weapon(new CowboyPistol(), 36, 18, bullets);
            }
            // if(weapon_name == "sniper"){
            //     return Weapon(new Sniper());
            // }
            // if(weapon_name == "shotgun"){
            //     return Weapon(new Shotgun());
            // }
            // if(weapon_name == "pew_pew"){
            //     return Weapon(new PewPew());
            // }
            if(weapon_name == "laser_rifle"){
                return Weapon(new LaserRifle(), 36, 18, bullets);
            }
            return Weapon(nullptr, 0, 0, bullets);
        }
};


#endif // WEAPON_FACTORY_H