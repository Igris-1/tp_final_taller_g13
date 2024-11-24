#include "game.h"
#include <algorithm>
#include <unistd.h>

Game::Game(int height, int width):
        map(width, height),
        ducks_states(),
        time_to_respawn(300),
        actual_round(0),
        started_game(false) {}

void Game::duck_exist(int id) {
    this->map.duck_exist(id);
    return;
}

void Game::remove_duck(int id) {
    this->map.remove_duck(id);
    this->ducks_states.erase(id);
}

void Game::run_duck(int duck_id, bool left, bool right) {
    try {
        this->map.duck_is_alive(duck_id);
        if (!this->ducks_states[duck_id]->is_moving_left) {
            this->ducks_states[duck_id]->is_moving_left = left;
        }
        if (!this->ducks_states[duck_id]->is_moving_right) {
            this->ducks_states[duck_id]->is_moving_right = right;
        }
    } catch (GameError& e) {
        return;
    }
}

void Game::set_duck_start_position(int id, int x, int y) {
    if (this->map.set_duck_start_position(id, x, y)) {
        ducks_states.emplace(id, std::make_shared<duck_state>());
        this->ducks_score[id] = 0;
    }
}

std::vector<duck_DTO> Game::get_duck_DTO_list() {
    std::vector<duck_DTO> list_DTO = this->map.get_duck_DTO_list();
    for (auto& it: list_DTO) {
        it.is_moving_left = this->ducks_states[it.duck_id]->is_moving_left;
        it.is_moving_right = this->ducks_states[it.duck_id]->is_moving_right;
        it.jumping = this->ducks_states[it.duck_id]->is_jumping;
        it.falling = this->ducks_states[it.duck_id]->is_falling;
        it.shooting = this->ducks_states[it.duck_id]->holding_action;
    }
    return list_DTO;
}

score_DTO Game::get_score_DTO() {

    score_DTO score;

    std::vector<std::pair<int, int>> sorted_ducks(this->ducks_score.begin(),
                                                  this->ducks_score.end());

    std::sort(sorted_ducks.begin(), sorted_ducks.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    if (!sorted_ducks.empty()) {
        score.first_place_id = sorted_ducks[0].first;
        score.first_place_score = sorted_ducks[0].second;
    }
    if (sorted_ducks.size() > 1) {
        score.second_place_id = sorted_ducks[1].first;
        score.second_place_score = sorted_ducks[1].second;
    }
    if (sorted_ducks.size() > 2) {
        score.third_place_id = sorted_ducks[2].first;
        score.third_place_score = sorted_ducks[2].second;
    }
    if (sorted_ducks.size() > 3) {
        score.fourth_place_id = sorted_ducks[3].first;
        score.fourth_place_score = sorted_ducks[3].second;
    }
    return score;
}

void Game::respawner() { this->map.respawn_ducks(); }

void Game::continue_horizontal_movements(int count) {
    std::vector<int> ducks_id = this->map.get_live_duck_ids();

    for (int i = 0; i < count; i++) {
        for (auto& id: ducks_id) {
            // se mueve para la left si is_moving_left is true
            if (this->ducks_states[id]->is_moving_left) {
                this->ducks_states[id]->facing_direction = false;
                this->map.move_relative_if_posible(id, LEFT_MOVEMENT, 0);
            }
            // se mueve para la right si is_moving_right is true
            if (this->ducks_states[id]->is_moving_right) {
                this->ducks_states[id]->facing_direction = true;
                this->map.move_relative_if_posible(id, RIGHT_MOVEMENT, 0);
            }
        }
    }
    for (int j = 0; j < count * 4; j++) {
        this->map.bullets_next_movement();
    }

    for (int j = 0; j < (count * 3); j++) {
        this->map.inertia_weapon();
    }
}

void Game::continue_vertical_movements(int count) {
    std::vector<int> ducks_id = this->map.get_all_duck_ids();
    for (auto& id: ducks_id) {
        if (this->ducks_states[id]->is_jumping) {
            for (int i = 0; i < (count * PRODUCT_FACTOR_JUMP) + ADD_FACTOR_JUMP; i++) {
                if (this->ducks_states[id]->tiles_to_jump > 0) {
                    this->map.move_relative_if_posible(id, 0, JUMP_DIRECTION);
                    this->ducks_states[id]->tiles_to_jump--;
                }
                if (this->ducks_states[id]->tiles_to_jump == 0) {
                    this->ducks_states[id]->air_time--;
                }
                if (this->ducks_states[id]->tiles_to_jump == 0 &&
                    this->ducks_states[id]->air_time == 0) {
                    this->ducks_states[id]->is_jumping = false;
                    this->ducks_states[id]->is_falling = true;
                }
            }
        } else if (this->ducks_states[id]->falling_with_style) {
            for (int i = 0; i < (count) + ADD_FACTOR_GRAVITY; i++) {
                if (this->ducks_states[id]->falling_with_style && i % 2 == 0) {
                    this->ducks_states[id]->is_falling =
                            this->map.move_relative_if_posible(id, 0, GRAVITY) ? true : false;
                }
            }
        } else {
            for (int i = 0; i < (count * PRODUCT_FACTOR_GRAVITY) + ADD_FACTOR_GRAVITY; i++) {
                // this->ducks_states[it->first]->is_falling = this->map.move_duck(it->second, 0,
                // GRAVITY);
                if (this->map.move_relative_if_posible(id, 0, GRAVITY)) {
                    this->ducks_states[id]->is_falling = true;
                } else {
                    this->ducks_states[id]->is_falling = false;
                }
            }
        }
    }

    for (int j = 0; j < (count * PRODUCT_FACTOR_GRAVITY) + ADD_FACTOR_GRAVITY; j++) {
        this->map.gravity_weapon();
    }
}

void Game::stop_run_duck(int id, bool stop_left, bool stop_right) {
    if (!this->map.duck_exist(id)) {
        return;
    }
    if (stop_left) {
        this->ducks_states[id]->is_moving_left = !stop_left;
    }
    if (stop_right) {
        this->ducks_states[id]->is_moving_right = !stop_right;
    }
}

game_snapshot_t Game::get_snapshot() {
    game_snapshot_t snapshot;
    snapshot.ducks = this->get_duck_DTO_list();  // usar el de this y no el de map
    snapshot.ducks_len = snapshot.ducks.size();
    snapshot.bullets = this->map.get_bullets_DTO_list();
    snapshot.bullets_len = snapshot.bullets.size();
    snapshot.weapons = this->map.get_weapons_DTO_list();
    snapshot.weapons_len = snapshot.weapons.size();
    snapshot.boxes = this->map.get_boxes_DTO();
    snapshot.boxes_len = snapshot.boxes.size();
    return snapshot;
}

map_structure_t Game::get_map_structure() {
    map_structure_t map_structure;
    map_structure.platforms = this->map.get_platforms_DTO();
    map_structure.platforms_len = static_cast<uint16_t>(map_structure.platforms.size());
    return map_structure;
}

void Game::jump_duck(int id, bool jump) {
    if (!this->map.duck_exist(id) && !this->map.duck_is_alive(id)) {
        return;
    }
    if (jump) {
        this->ducks_states[id]->falling_with_style = true;
    }
    if (!this->ducks_states[id]->is_jumping && jump &&
        !this->ducks_states[id]->is_falling) {  // esto no es suficiente para evitar que vuele

        this->ducks_states[id]->is_jumping = true;
        this->ducks_states[id]->tiles_to_jump = TILES_FOR_JUMP;
        this->ducks_states[id]->air_time = 40;
    }
    if (jump && this->ducks_states[id]->is_falling) {
        this->ducks_states[id]->falling_with_style = true;
    }
}

void Game::stop_jump_duck(int id, bool stop_jump) {
    if (stop_jump) {
        this->ducks_states[id]->falling_with_style = false;
    }
}

void Game::use_duck_item(int id, bool fire) {
    if (fire && this->map.duck_is_alive(id)) {
        this->ducks_states[id]->holding_action = true;
        this->map.use_item(id, this->ducks_states[id]->facing_direction, false);
    }
}

void Game::keep_using_item() {
    std::vector<int> ducks_id = this->map.get_live_duck_ids();
    for (auto& id: ducks_id) {
        this->map.continue_fire_rate(id);
        if (this->ducks_states[id]->holding_action) {
            this->map.use_item(id, this->ducks_states[id]->facing_direction, true);
        }
    }
}

void Game::add_spawn_position(int x, int y) {
    // this->map.approximate_spawn_to_platform(x, y, 36, 18);
    this->spawn_positions.push_back(std::make_tuple(x, y));
}

void Game::stop_duck_item(int id, bool stop_fire) {
    if (stop_fire) {
        this->ducks_states[id]->holding_action = false;
        return;
    }
}

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

void Game::add_item_on_map(std::string type, int x, int y) {
    if(type == "helmet"){
        std::shared_ptr<Helmet> helmet = std::make_shared<Helmet>(32, 32);
        this->map.add_item(helmet, x, y);
        return;
    }else if(type == "armor"){
        std::shared_ptr<Armor> armor = std::make_shared<Armor>(40, 40);
        this->map.add_item(armor, x, y);
        return;
    }
    std::shared_ptr<Weapon> weapon = std::make_shared<Weapon>(
            WeaponFactory::createWeapon(this->map.get_bullets_list(), type));
    this->map.add_item(weapon, x, y);
}

void Game::pick_up_item(int duck_id, bool pick_up) {
    if (!pick_up || !this->map.duck_exist(duck_id) || !this->map.duck_is_alive(duck_id)) {
        return;
    }
    this->map.ducks_try_throw(duck_id, this->ducks_states[duck_id]->facing_direction);
}

void Game::throw_item(int id, bool throw_item){
    if (!throw_item || !this->map.duck_exist(id) || !this->map.duck_is_alive(id)) {
        return;
    }
    this->map.throw_item(id, this->ducks_states[id]->facing_direction);
}

void Game::start_game() {
    this->started_game = true;
    this->actual_round += 1;
    std::vector<int> ids_ducks = this->map.get_live_duck_ids();
    for (auto& id: ids_ducks) {
        this->ducks_score[id] = 0;
    }
}
bool Game::check_if_round_finished() {
    std::vector<int> ids_ducks = this->map.get_live_duck_ids();
    int dead_ducks = this->map.ducks_dead_size();
    if (ids_ducks.size() <= 1 && dead_ducks > 0) {
        if (ids_ducks.size() == 1) {
            this->ducks_score[ids_ducks[0]] += 1;
        }
        return true;
    }
    return false;
}

bool Game::check_if_winner() {
    for (auto it = ducks_score.begin(); it != ducks_score.end(); ++it) {
        if (it->second == 10) {
            return true;
        }
    }
    return false;
}

void Game::random_weapon_spawn(bool on_game) {
    if (on_game && this->time_to_respawn > 0) {
        this->time_to_respawn -= 1;
        return;
    }
    for (auto& pos: this->spawn_positions) {
        if (this->map.already_exist_a_pickable(std::get<0>(pos), std::get<1>(pos))) {
            continue;
        } else {
            this->map.add_item(std::make_shared<Weapon>(WeaponFactory::createWeapon(
                                         this->map.get_bullets_list(), "random")),
                                 std::get<0>(pos), std::get<1>(pos));
        }
    }
    this->time_to_respawn = TIME_TO_RESPAWN;
}

// preguntar por esto
void Game::reset_round() {
    this->map.clean_map();
    this->actual_round += 1;
    for (auto& pos: this->spawn_positions) {
        this->random_weapon_spawn(false);
    }
}
