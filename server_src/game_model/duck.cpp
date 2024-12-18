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
        Positionable(DEFAULT_X, DEFAULT_Y, DUCK_WIDTH, DUCK_HEIGHT),
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
    return this->item_in_hands->get_id() != NO_WEAPON_ID;
}

void Duck::add_armor() {
    this->has_armor = true;
    this->item_in_hands = nullptr;
}

void Duck::add_helmet() {
    this->has_helmet = true;
    this->item_in_hands = nullptr;
}

bool Duck::is_alive() { return !(this->health <= NO_LIFE); }

void Duck::receive_damage(int damage) {
    if (damage == NO_DAMAGE) {
        return;
    }
    if (this->has_armor) {
        this->has_armor = false;
        return;
    } else if (this->has_helmet) {
        this->has_helmet = false;
        return;
    }
    this->health -= damage;
    if (this->health < NO_LIFE) {
        this->health = NO_LIFE;
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
        dto.weapon_id = NO_WEAPON_ID;
    } else {
        dto.weapon_id = this->item_in_hands->get_id();
    }
    return dto;
}

int Duck::continue_fire_rate(int speed_of_game) {
    if (!this->has_item()) {
        return EXIT_SUCCESS;
    }
    this->item_in_hands->fire_rate_down();

    if(item_in_hands->is_explosive() && item_in_hands->is_active()){
        for(int i = 0; i < speed_of_game; i++){            
            this->item_in_hands->fire_rate_down();
        }
        if(item_in_hands->exploted()){
            return GRENADE_EXPLOTED_ON_HAND;
        }
    }
    return EXIT_SUCCESS;
}

int Duck::use_item(int x_direction, int y_direction, bool is_holding) {
    if (!this->has_item()) {
        return EXIT_SUCCESS;
    }
    this->item_in_hands->set_direction(x_direction, y_direction);
    this->item_in_hands->set_holding(is_holding);
    int sound = this->item_in_hands->get_sound();
    this->item_in_hands->use();
    return sound;
}


void Duck::tick_respawn_time() {
    if (this->respawn_time > 0) {
        this->respawn_time--;
    }
}

int Duck::get_respawn_time() { return this->respawn_time; }

void Duck::set_health(int health) {
    this->health = health;
    this->respawn_time = RESPAWN_TIME;
}

void Duck::kill() { this->health = NO_LIFE; }

void Duck::set_direction(int step_dx, int step_dy) {
    if (step_dx != 0) {
        this->x_direction = step_dx;
    }
    this->y_direction = step_dy;
}

int Duck::get_x_direction() { return this->x_direction; }

int Duck::get_y_direction() { return this->y_direction; }

void Duck::set_sliding(bool sliding) { this->is_sliding = sliding; }

void Duck::move_duck_relative(int x, int y) {
    if (this->is_sliding) {
        this->suffering_recoil =
                false;
        this->hitbox.move_relative(this->x_direction, y);
        this->sliding_counter--;
        if (this->sliding_counter <= 0) {
            this->is_sliding = false;
            this->sliding_counter = SLIDING_COUNTER;
        }
        return;
    }
    if (this->suffering_recoil) {
        this->hitbox.move_relative(-this->x_direction, y);
        this->recoil_counter--;
        if (this->recoil_counter <= 0) {
            this->suffering_recoil = false;
            this->recoil_counter = 0;
        }
        return;
    }
    this->hitbox.move_relative(x, y);
}

bool Duck::get_is_sliding() { return this->is_sliding; }

bool Duck::has_recoil() { return this->suffering_recoil; }

void Duck::set_recoil(int recoil) {
    if (recoil == NO_RECOIL_CODE) {
        this->suffering_recoil = false;
        this->recoil_counter = NO_RECOIL;
        return;
    }
    this->suffering_recoil = true;
    this->recoil_counter = recoil;
}