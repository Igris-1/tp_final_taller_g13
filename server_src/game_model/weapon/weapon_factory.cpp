#include "weapon_factory.h"

#include "weapons_strategy/weapon.h"
#include "helmet.h"
#include "armor.h"

std::string last_weapon = "";

std::shared_ptr<Pickable> WeaponFactory::createWeapon(std::list<std::shared_ptr<BulletInterface>>& bullets,
                                   std::string weapon_name) {
    static const std::vector<std::string> weapon_names = 
    {"cowboy", "laser_rifle", "AK47", "shotgun", "armor", "helmet" };
    if (weapon_name == "cowboy") {
        return std::make_shared<Weapon>(new CowboyPistol(), 36, 18, bullets);
    }
    if (weapon_name == "AK47") {
        return std::make_shared<Weapon>(new AK47(), 64, 64, bullets);
    }
    if (weapon_name == "shotgun") {
        return std::make_shared<Weapon>(new Shotgun(), 64, 64, bullets);
    }
    // if(weapon_name == "pew_pew"){
    //     return Weapon(new PewPew());
    // }
    if (weapon_name == "laser_rifle") {
        return std::make_shared<Weapon>(new LaserRifle(), 64, 64, bullets);
    }
    if(weapon_name == "armor"){
        return std::make_shared<Armor>(25,25);
    }
    if(weapon_name == "helmet"){
        return std::make_shared<Helmet>(30, 30);
    }
    if (weapon_name == "random") {
        std::srand(static_cast<unsigned>(std::time(0)));
        int rand_choice = std::rand() % weapon_names.size();
        if (weapon_names[rand_choice] == last_weapon) {
            rand_choice = (rand_choice + 1) % weapon_names.size();
        }
        return createWeapon(bullets, weapon_names[rand_choice]);
    }
    
    std::cout << "Weapon not found: " << weapon_name << std::endl;
    return nullptr;
}