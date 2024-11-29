#include "weapon_factory.h"

#include <cstdlib>
#include <ctime>

#include "../pickable.h"
#include "weapons_strategy/weapon.h"

#include "armor.h"
#include "banana.h"
#include "grenade.h"
#include "helmet.h"

#define SIZE_ARMOR 24
#define SIZE_HELMET 30

std::string last_weapon = "";
int i = -1;

std::shared_ptr<Pickable> WeaponFactory::createWeapon(
        std::list<std::shared_ptr<BulletInterface>>& bullets, std::string weapon_name,
        const std::map<std::string, weapon_config>& weapons_config) {

    static const std::vector<std::string> weapon_names = {
            "grenade",       "banana", "pew_pew_laser", "laser_rifle", "ak_47", "dueling_pistol",
            "cowboy_pistol", "magnum", "shotgun",       "sniper",      "armor", "helmet"};

#ifdef RANDOM
    if (weapon_name == "random") {
        std::srand(static_cast<unsigned>(std::time(0)));
        int rand_choice;
        do {
            rand_choice = std::rand() % weapon_names.size();
        } while (weapon_names[rand_choice] == last_weapon);
        last_weapon = weapon_names[rand_choice];
        return createWeapon(bullets, weapon_names[rand_choice], weapons_config);
    }
#endif
#ifndef RANDOM
    if (weapon_name == "random") {
        i++;
        if (i == weapon_names.size()) {
            i = 0;
        }
        std::cout << "intento crear: " << weapon_names[i] << std::endl;
        return createWeapon(bullets, weapon_names[i], weapons_config);
    }
#endif
    int width, height, shot, damage, recoil, scope, reload_time;
    auto it = weapons_config.find(weapon_name);
    if (it != weapons_config.end()) {
        std::cout << "arma encontrada: " << weapon_name << std::endl;
        width = it->second.hitbox_width;
        height = it->second.hitbox_height;
        shot = it->second.shot;
        damage = it->second.damage;
        recoil = it->second.recoil;
        scope = it->second.scope;
        reload_time = it->second.reload_time;
        std::cout << "\n\n"
                  << "arma creada: " << weapon_name << std::endl;
        std::cout << "\t\tshots: " << shot << std::endl;
        std::cout << "\t\tdamage: " << damage << std::endl;
        std::cout << "\t\trecoil: " << recoil << std::endl;
        std::cout << "\t\tscope: " << scope << std::endl;
        std::cout << "\t\treload_time: " << reload_time << std::endl;
        std::cout << "\n\n";
    }else{
        std::cout << "arma no encontrada: " << weapon_name << std::endl;
    }   

    if (weapon_name == "cowboy_pistol") {
        return std::make_shared<Weapon>(new CowboyPistol(shot, damage, recoil, scope, reload_time),
                                        width, height, bullets);
    }

    if (weapon_name == "dueling_pistol") {
        return std::make_shared<Weapon>(new DuelingPistol(shot, damage, recoil, scope, reload_time),
                                        width, height, bullets);
    }
    if (weapon_name == "magnum") {
        return std::make_shared<Weapon>(new Magnum(shot, damage, recoil, scope, reload_time), width,
                                        height, bullets);
    }
    if (weapon_name == "sniper") {
        return std::make_shared<Weapon>(new Sniper(shot, damage, recoil, scope, reload_time), width,
                                        height, bullets);
    }
    if (weapon_name == "pew_pew_laser") {
        return std::make_shared<Weapon>(new PewPew(shot, damage, recoil, scope, reload_time), width,
                                        height, bullets);
    }
    if (weapon_name == "ak_47") {
        return std::make_shared<Weapon>(new AK47(shot, damage, recoil, scope, reload_time), width,
                                        height, bullets);
    }
    if (weapon_name == "shotgun") {
        return std::make_shared<Weapon>(new Shotgun(shot, damage, recoil, scope, reload_time),
                                        width, height, bullets);
    }
    if (weapon_name == "grenade") {
        return std::make_shared<Grenade>(width, height, damage, scope, reload_time);
    }
    if (weapon_name == "laser_rifle") {
        return std::make_shared<Weapon>(new LaserRifle(shot, damage, recoil, scope, reload_time),
                                        width, height, bullets);
    }
    if (weapon_name == "armor") {
        return std::make_shared<Armor>(SIZE_ARMOR, SIZE_ARMOR);
    }
    if (weapon_name == "helmet") {
        return std::make_shared<Helmet>(SIZE_HELMET, SIZE_HELMET);
    }
    if (weapon_name == "banana") {
        return std::make_shared<Banana>(width, height);
    }
    std::cout << "Weapon not found: " << weapon_name << std::endl;
    return nullptr;
}