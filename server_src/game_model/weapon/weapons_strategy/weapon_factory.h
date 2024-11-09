#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include <string>
#include "weapon.h"
#include "cowboy_pistol.h"
#include "shotgun.h"
#include "sniper.h"
#include "pew_pew.h"
#include "laser_rifle.h"
#include "no_weapon.h"


class WeaponFactory {
    public:
        // "cowboy", "sniper", "shotgun", "pew_pew", "laser_rifle", "" (no weapon)
        static Weapon createWeapon(std::string weapon_name = ""){
            if (weapon_name == "cowboy") {
                return Weapon(0, 0, 0, new CowboyPistol());
            }
            // if(weapon_name == "sniper"){
            //     return Weapon(0, 0, 0, new Sniper());
            // }
            // if(weapon_name == "shotgun"){
            //     return Weapon(0, 0, 0, new Shotgun());
            // }
            // if(weapon_name == "pew_pew"){
            //     return Weapon(0, 0, 0, new PewPew());
            // }
            // if(weapon_name == "laser_rifle"){
            //     return Weapon(0, 0, 0, new LaserRifle());
            // }
            if(weapon_name == ""){
                return Weapon(0, 0, 0, new NoWeapon());
            }
        }
};


#endif // WEAPON_FACTORY_H