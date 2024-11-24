#include "weapon_factory.h"
#include "weapon.h"

std::string last_weapon = "";

Weapon WeaponFactory::createWeapon(std::list<std::shared_ptr<BulletInterface>>& bullets,
                               std::string weapon_name) {
        
        static const std::vector<std::string> weapon_names = {
        "cowboy", "laser_rifle", "AK47", "shotgun"};
        if (weapon_name == "cowboy") {
            return Weapon(new CowboyPistol(), 36, 18, bullets);
        }
        if(weapon_name == "AK47"){
            return Weapon(new AK47(), 36, 18, bullets);
        }
        if(weapon_name == "shotgun"){
            return Weapon(new Shotgun(), 36, 18, bullets);
        }
        // if(weapon_name == "pew_pew"){
        //     return Weapon(new PewPew());
        // }
        if (weapon_name == "laser_rifle") {
            return Weapon(new LaserRifle(), 36, 18, bullets);
        }
        if(weapon_name == "random"){
            std::srand(static_cast<unsigned>(std::time(0))); 
            int rand_choice = std::rand() % weapon_names.size();
            if(weapon_names[rand_choice]== last_weapon){
                rand_choice = (rand_choice + 1) % weapon_names.size();
            }
            return createWeapon(bullets, weapon_names[rand_choice]);
        }
        
        return Weapon(nullptr, 0, 0, bullets);
    }