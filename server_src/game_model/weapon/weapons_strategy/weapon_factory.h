#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include <string>

#include "cowboy_pistol.h"
#include "laser_rifle.h"
#include "pew_pew.h"
#include "shotgun.h"
#include "sniper.h"
#include "weapon.h"

#include <cstdlib>
#include <ctime>


class WeaponFactory {
public:
    // "cowboy", "sniper", "shotgun", "pew_pew", "laser_rifle", "" (no weapon)
    static Weapon createWeapon(std::list<std::shared_ptr<BulletInterface>>& bullets,
                               std::string weapon_name = "") {
        
        static const std::vector<std::string> weapon_names = {
        "cowboy", "laser_rifle"};
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
        if (weapon_name == "laser_rifle") {
            return Weapon(new LaserRifle(), 36, 18, bullets);
        }
        if(weapon_name == "random"){
            std::srand(static_cast<unsigned>(std::time(0))); 
            int rand_choice = std::rand() % weapon_names.size();
            return createWeapon(bullets, weapon_names[rand_choice]);
        }
        
        return Weapon(nullptr, 0, 0, bullets);
    }
};


#endif  // WEAPON_FACTORY_H