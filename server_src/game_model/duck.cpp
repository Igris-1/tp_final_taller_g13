#include "duck.h"

#include <iostream>
#include <typeinfo>

#include "weapon/weapons_strategy/weapon.h"

#include "map_game.h"
#include "pickable.h"

Duck::Duck(int health, int id):
        health(health),
        begin_health(health),
        item_in_hands(nullptr),
        Positionable(-1, -1, DUCK_WIDTH, DUCK_HEIGHT),
        duck_id(id) {
            this->has_armor = false;
            this->has_helmet = false;
        }

void Duck::reset() {
    this->has_armor = false;
    this->has_helmet = false;
    this->health = this->begin_health;
    this->item_in_hands = nullptr;
}
std::shared_ptr<Pickable> Duck::throw_item() {
    if (!this->has_item()) {
        return nullptr;
    }
    return this->take_item(nullptr);
}

int Duck::get_health() { return this->health; }

int Duck::get_id() { return this->duck_id; }

std::shared_ptr<Pickable> Duck::take_item(std::shared_ptr<Pickable> item) {
    std::shared_ptr<Pickable> aux = this->item_in_hands;
    if (item == nullptr) {
        this->item_in_hands = item;
        return aux;
    }
    this->item_in_hands = item;
    this->item_in_hands->set_falling(false);
    this->item_in_hands->set_moving(true);
    this->item_in_hands->add_owner(shared_from_this());
    return aux;
}

bool Duck::has_item() {
    if (this->item_in_hands == nullptr) {
        return false;
    }
    return this->item_in_hands->get_id() != 0;
}

void Duck::add_armor() { 
    this->has_armor = true;
   this->item_in_hands = nullptr;
}

void Duck::add_helmet() { 
    this->has_helmet = true;
    this->item_in_hands = nullptr;
}

bool Duck::is_alive() { return !(this->health <= 0); }

void Duck::receive_damage(int damage) {
    if (this->has_armor) {
        this->has_armor = false;
        return;
    } else if (this->has_helmet) {
        this->has_helmet = false;
        return;
    }
    this->health -= damage;
    if (this->health < 0) {
        this->health = 0;
    }
}

Hitbox Duck::get_hitbox() { return this->hitbox; }

Hitbox& Duck::get_hitbox_reference() { return this->hitbox; }

bool Duck::is_this_duck(int id) { return this->duck_id == id; }

duck_DTO Duck::to_DTO() {
    duck_DTO dto;
    dto.duck_id = this->duck_id;
    dto.x = this->hitbox.get_x();
    dto.y = this->hitbox.get_y();
    dto.width = this->hitbox.get_width();
    dto.height = this->hitbox.get_height();
    dto.armor_equipped = this->has_armor;
    dto.helmet_equipped = this->has_helmet;
    if (item_in_hands == nullptr) {
        dto.weapon_id = 0;
    } else {
        dto.weapon_id = this->item_in_hands->get_id();
    }
    return dto;
}

void Duck::continue_fire_rate() {
    if(!this->has_item()) {
        return;
    }
    this->item_in_hands->fire_rate_down();
}

// bool Duck::has_explosive_weapon() {
//     if (this->item_in_hands == nullptr) {
//         return false;
//     }
//     return this->item_in_hands->is_explosive();
// }

// bool Duck::has_active_explosive_weapon() {
//     if (this->item_in_hands == nullptr) {
//         return false;
//     }
//     return this->item_in_hands->is_active();
// }
// void Duck::activation_explosive_weapon() {
//     if (this->weap == nullptr) {
//         return;
//     }
//     this->weapon->activation();
// }

// bool Duck::already_exploted() {
//     this->item_in_hands->move_to(this->get_x(), this->get_y());
//     return this->item_in_hands->exploded();
// }

void Duck::use_item(int x_direction, int y_direction, MapGame& map, bool is_holding) {
    if (!this->has_item()) {
        return;
    }
    this->item_in_hands->set_direction(x_direction, y_direction);
    this->item_in_hands->set_holding(is_holding);
    this->item_in_hands->use();
    if(item_in_hands== nullptr){
        return;
    }
    int recoil = this->item_in_hands->recoil_produced();
    map.move_relative_if_posible(this->duck_id, (-x_direction) * recoil, 0);
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

void Duck::kill(){
    this->health = 0;
}