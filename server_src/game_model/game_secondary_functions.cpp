#include "game.h"

void Game::add_invalid_position(Hitbox hitbox) {
    if (!this->map.add_invalid_position(hitbox)) {
        throw GameError("game can't add invalid position");
    }
}

void Game::add_new_platform(Hitbox hitbox) {
    if (!this->map.add_platform(hitbox)) {
        throw GameError("game can't add platform");
    }
}

void Game::add_box(Hitbox hitbox) { this->map.add_box(hitbox); }

void Game::duck_exist(int id) {
    this->map.duck_exist(id);
    return;
}

void Game::gravity_movement(int id_duck) {
    for (int i = 0; i < (SPEED_OF_GAME * PRODUCT_FACTOR_GRAVITY) + ADD_FACTOR_GRAVITY; i++) {
        if (this->map.move_relative_if_posible(id_duck, 0, GRAVITY)) {
            this->ducks_states[id_duck]->is_falling = true;
        } else {
            this->ducks_states[id_duck]->is_falling = false;
        }
    }
}

void Game::jump_movement(int id_duck) {
    for (int i = 0; i < (SPEED_OF_GAME * PRODUCT_FACTOR_JUMP) + ADD_FACTOR_JUMP; i++) {
        if (this->ducks_states[id_duck]->tiles_to_jump > 0) {
            this->map.move_relative_if_posible(id_duck, 0, JUMP_DIRECTION);
            this->ducks_states[id_duck]->tiles_to_jump--;
        }
        if (this->ducks_states[id_duck]->tiles_to_jump == 0) {
            this->ducks_states[id_duck]->air_time--;
        }
        if (this->ducks_states[id_duck]->tiles_to_jump == 0 &&
            this->ducks_states[id_duck]->air_time == 0) {
            this->ducks_states[id_duck]->is_jumping = false;
            this->ducks_states[id_duck]->is_falling = true;
        }
    }
}

void Game::jump_with_style(int id_duck) {
    for (int i = 0; i < (SPEED_OF_GAME) + ADD_FACTOR_GRAVITY; i++) {
        if (this->ducks_states[id_duck]->falling_with_style && i % 2 == 0) {
            this->ducks_states[id_duck]->is_falling =
                    this->map.move_relative_if_posible(id_duck, 0, GRAVITY) ? true : false;
        }
    }
}

void Game::load_platforms(std::vector<std::tuple<int, int, int, int>>& spawns) {
    for (auto& platform: spawns) {
        this->add_new_platform(
                Hitbox(std::get<X_POSITION>(platform), std::get<Y_POSITION>(platform),
                       std::get<WIDTH_POSITION>(platform), std::get<HEIGHT_POSITION>(platform)));
    }
}

void Game::load_boxes(std::vector<std::tuple<int, int, int, int>>& spawns) {
    for (auto& box: spawns) {
        this->add_box(Hitbox(std::get<X_POSITION>(box), std::get<Y_POSITION>(box),
                             std::get<WIDTH_POSITION>(box), std::get<HEIGHT_POSITION>(box)));
    }
}

void Game::load_spawn_ducks(std::vector<std::tuple<int, int, int, int>>& spawns) {
    for (auto& duck_spawn: spawns) {
        this->add_spawn_duck(Hitbox(
                std::get<X_POSITION>(duck_spawn), std::get<Y_POSITION>(duck_spawn),
                std::get<WIDTH_POSITION>(duck_spawn), std::get<HEIGHT_POSITION>(duck_spawn)));
    }
}

void Game::load_spawn_weapons(std::vector<std::tuple<int, int, int, int>>& spawns) {
    for (auto& weapon_spawn: spawns) {
        this->add_spawn_position(Hitbox(
                std::get<X_POSITION>(weapon_spawn), std::get<Y_POSITION>(weapon_spawn),
                std::get<WIDTH_POSITION>(weapon_spawn), std::get<HEIGHT_POSITION>(weapon_spawn)));
    }
}