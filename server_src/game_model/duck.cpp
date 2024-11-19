#include "duck.h"

#include <iostream>
#include "pickable.h"
#include "map_game.h"
#include "weapon/weapons_strategy/weapon.h"

// Duck::Duck(int health) : health(health), armor(0), helmet(0), weapon(0), Positionable(-1,-1),
// duck_id(0) {}

Duck::Duck(int health, int id):
        health(health),
        begin_health(health),
        weapon(nullptr),
        Positionable(-1, -1, DUCK_WIDTH, DUCK_HEIGHT),
        duck_id(id) {}

void Duck::reset(){
    this->health = this->begin_health;
    this->weapon = nullptr;
    //this->respawn_time = 0;
}
std::shared_ptr<Weapon> Duck::throw_weapon() {
    if (this->weapon == nullptr) {
        std::cout << "no weapon" << std::endl;
        return nullptr;
    }
    auto weapon_list = this->weapon->get_list();
    return this->take_weapon(nullptr);
}

int Duck::get_health() { return this->health; }

int Duck::get_id() { return this->duck_id; }

std::shared_ptr<Weapon> Duck::take_weapon(std::shared_ptr<Weapon> weapon) {
    std::shared_ptr<Weapon> aux = this->weapon;
    if (weapon == nullptr) {
        // std::list<std::shared_ptr<BulletInterface>> weapon_list;
        // aux = std::make_shared<Weapon>(WeaponFactory::createWeapon(weapon_list, ""));
        this->weapon = weapon;
        return aux;
    }

    this->weapon = weapon;
    this->weapon->set_falling(false);
    this->weapon->set_moving(true);
    return aux;
}


// std::shared_ptr<Armor> Duck::take_armor(std::shared_ptr<Armor> armor) {
//     std::shared_ptr<Armor> aux = this->armor;
//     this->armor = armor;
//     return aux;
// }

// std::shared_ptr<Helmet> Duck::take_helmet(std::shared_ptr<Helmet> helmet) {
//     std::shared_ptr<Helmet> aux = this->helmet;
//     this->helmet = helmet;
//     return aux;
// }

bool Duck::has_weapon() {
    if (this->weapon == nullptr) {
        return false;
    }
    return this->weapon->get_id() != 0;
}

void Duck::add_armor(){
    this->has_armor = true;
}

void Duck::add_helmet(){
    this->has_helmet = true;
}



bool Duck::is_alive() { return !(this->health <= 0); }

void Duck::receive_damage(int damage) {
    if(this->has_armor){
        this->has_armor = false;
        return;
    }else if(this->has_helmet){
        this->has_helmet = false;
        return;
    }
    this->health -= damage;
    if (this->health < 0) {
        this->health = 0;
    }
}

Hitbox Duck::get_hitbox() { return this->hitbox; }

bool Duck::is_this_duck(int id) { return this->duck_id == id; }

duck_DTO Duck::to_DTO() {
    duck_DTO dto;
    dto.duck_id = this->duck_id;
    dto.x = this->hitbox.get_x();
    dto.y = this->hitbox.get_y();
    dto.width = this->hitbox.get_width();
    dto.height = this->hitbox.get_height();
    // uint8_t duck_hp = this->health;
    if (weapon == nullptr) {
        dto.weapon_id = 0;
    } else {
        dto.weapon_id = this->weapon->get_id();
    }
    // bool helmet_equipped;
    // bool armor_equipped;
    return dto;
}

void Duck::continue_fire_rate() {
    if (this->weapon == nullptr) {
        return;
    }
    this->weapon->fire_rate_down();
}

bool Duck::has_explosive_weapon() {
    if (this->weapon == nullptr) {
        return false;
    }
    return this->weapon->is_explosive();
}

bool Duck::has_active_explosive_weapon() {
    if (this->weapon == nullptr) {
        return false;
    }
    return this->weapon->is_active();
}
void Duck::activation_explosive_weapon() {
    if (this->weapon == nullptr) {
        return;
    }
    this->weapon->activation();
}

bool Duck::already_exploted() {
    this->weapon->move_to(this->get_x(), this->get_y());
    return this->weapon->exploted();
}

void Duck::use_item(int x_direction, int y_direction, MapGame& map) {
    if (!this->has_weapon()) {
        return;
    }
    this->weapon->set_direction(x_direction, y_direction);
    this->weapon->add_owner(shared_from_this());
    this->weapon->use();

    int recoil = this->weapon->recoil_produced();
    map.move_relative_if_posible(this->duck_id, (-x_direction) * recoil, -recoil);
}


void Duck::tick_respawn_time() {
    if (this->respawn_time > 0) {
        this->respawn_time--;
    }
}

int Duck::get_respawn_time() { return this->respawn_time; }

void Duck::set_health(int health) {
    this->health = health;
    this->respawn_time = 100;
}
