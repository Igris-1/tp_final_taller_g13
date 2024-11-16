#include "duck.h"

#include <iostream>

#include "map_game.h"

// Duck::Duck(int health) : health(health), armor(0), helmet(0), weapon(0), Positionable(-1,-1),
// duck_id(0) {}

Duck::Duck(int health, int id):
        health(health),
        armor(nullptr),
        helmet(nullptr),
        weapon(nullptr),
        Positionable(-1, -1, DUCK_WIDTH, DUCK_HEIGHT),
        duck_id(id) {}

std::shared_ptr<Weapon> Duck::throw_weapon() {
    if (this->weapon == nullptr) {
        std::cout << "no weapon" << std::endl;
        return nullptr;
    }
    auto weapon_list = this->weapon->get_list();
    return this->take_weapon(
            nullptr);  // std::make_shared<Weapon>(WeaponFactory::createWeapon(weapon_list, ""))
    //    if(this->weapon == nullptr){
    //        return nullptr;
    //    }
    //    std::cout << "entro a throw_weapon" << std::endl;
    //     std::shared_ptr<Weapon> aux = this->weapon;
    //     this->weapon = std::make_shared<Weapon>(WeaponFactory::createWeapon(""));
    //     return aux;
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


std::shared_ptr<Armor> Duck::take_armor(std::shared_ptr<Armor> armor) {
    std::shared_ptr<Armor> aux = this->armor;
    this->armor = armor;
    return aux;
}

std::shared_ptr<Helmet> Duck::take_helmet(std::shared_ptr<Helmet> helmet) {
    std::shared_ptr<Helmet> aux = this->helmet;
    this->helmet = helmet;
    return aux;
}

bool Duck::has_weapon() {
    if (this->weapon == nullptr) {
        return false;
    }
    return this->weapon->get_id() != 0;
}

/*Weapon& Duck::get_weapon(){
    return this->weapon;
}*/

// Armor& Duck::get_armor(){
//     return this->armor;
// }

// Helmet& Duck::get_helmet(){
//     return this->helmet;
// }

bool Duck::is_alive() { return !(this->health <= 0); }

void Duck::receive_damage(int damage) {
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

std::vector<std::shared_ptr<BulletInterface>> Duck::fire_weapon(int x_direction, int y_direction,
                                                                MapGame& map) {

#ifndef NUEVO_MAPA
    if (!this->has_weapon()) {
        return std::vector<std::shared_ptr<BulletInterface>>();
    }
    std::vector<std::shared_ptr<BulletInterface>> bullets = this->weapon->fire(
            shared_from_this(), this->hitbox.get_x() + (this->hitbox.get_width() / 2),
            this->hitbox.get_y() + (this->hitbox.get_height()) / 2, x_direction, y_direction);
    int recoil = this->weapon->recoil_produced();
    if (map.can_move_hitbox(this->hitbox, (-x_direction) * recoil, -recoil)) {
        this->hitbox.move_relative((-x_direction) * recoil, -recoil);
    }
    return bullets;
#endif

#ifdef NUEVO_MAPA
    if (!this->has_weapon()) {
        return std::vector<std::shared_ptr<BulletInterface>>();
    }
    std::vector<std::shared_ptr<BulletInterface>> bullets = this->weapon->fire(
            shared_from_this(), this->hitbox.get_x() + (this->hitbox.get_width() / 2),
            this->hitbox.get_y() + (this->hitbox.get_height()) / 2, x_direction, y_direction);
    int recoil = this->weapon->recoil_produced();
    map.move_relative_if_posible(this->duck_id, (-x_direction) * recoil, -recoil);
    return bullets;
#endif
}

void Duck::use_item(int x_direction, int y_direction, MapGame& map) {
    if (!this->has_weapon()) {
        return;
    }
    this->weapon->set_direction(x_direction, y_direction);
    std::cout << "add owner" << std::endl;
    this->weapon->add_owner(shared_from_this());
    std::cout << "use a la weapon" << std::endl;
    this->weapon->use();
    std::cout << "ya use la weapon" << std::endl;

#ifndef NUEVO_MAPA
    int recoil = this->weapon->recoil_produced();
    if (map.can_move_hitbox(this->hitbox, (-x_direction) * recoil, -recoil)) {
        this->hitbox.move_relative((-x_direction) * recoil, -recoil);
    }
#endif

#ifdef NUEVO_MAPA
    int recoil = this->weapon->recoil_produced();
    map.move_relative_if_posible(this->duck_id, (-x_direction) * recoil, -recoil);
#endif
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
