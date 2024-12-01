#include "game.h"
#include <algorithm>
#include <unistd.h>

Game::Game(GameConfig& config):
        map(config.get_map_width(), config.get_map_height(), config.get_duck_config().health),
        ducks_states(),
        time_to_respawn(TIME_TO_RESPAWN),
        actual_round(0),
        started_game(false),
        ducks_config(config.get_duck_config()),
        weapons_config(config.get_weapon_config()),
        TILES_FOR_JUMP(config.get_duck_config().tiles_per_jump),
        PRODUCT_FACTOR_JUMP(config.get_duck_config().product_factor_jump),
        ADD_FACTOR_JUMP(config.get_duck_config().add_factor_jump),
        PRODUCT_FACTOR_GRAVITY(config.get_duck_config().product_factor_gravity),
        ADD_FACTOR_GRAVITY(config.get_duck_config().add_factor_gravity),
        SPEED_OF_GAME(config.get_duck_config().speed_of_game) {}



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
        it.crouching = this->ducks_states[it.duck_id]->crouching;
        it.looking_up = this->ducks_states[it.duck_id]->looking_up;
    }
    return list_DTO;
}

score_DTO Game::get_score_DTO() {

    score_DTO score;

    std::vector<std::pair<int, int>> sorted_ducks(this->ducks_score.begin(),
                                                  this->ducks_score.end());

    std::sort(sorted_ducks.begin(), sorted_ducks.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });
    
    score.amount_of_ducks = static_cast<uint8_t>(sorted_ducks.size());

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

void Game::continue_horizontal_movements() {
    std::vector<int> ducks_id = this->map.get_live_duck_ids();

    for (int i = 0; i < SPEED_OF_GAME; i++) {
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
            this->map.move_relative_if_posible(id, 0,
                                               0);  // no borrar :], hace q el pato siga patinandose
        }
    }
    for (int j = 0; j < SPEED_OF_GAME * 4; j++) {
        this->map.bullets_next_movement(this->weapons_config);
        this->map.explosives_on_map();
    }

    for (int j = 0; j < (SPEED_OF_GAME * 3); j++) {
        this->map.inertia_weapon();
    }
}

void Game::continue_vertical_movements() {
    std::vector<int> ducks_id = this->map.get_all_duck_ids();

    for (auto& id: ducks_id) {
        if (this->ducks_states[id]->trying_to_stand) {
            if (this->map.crouch_duck(id, false)) {
                this->ducks_states[id]->crouching = false;
                this->ducks_states[id]->trying_to_stand = false;
            }
        }
        if (this->ducks_states[id]->is_jumping) {
            this->jump_movement(id);
        } else if (this->ducks_states[id]->falling_with_style) {
            this->jump_with_style(id);
        } else {
            this->gravity_movement(id);
        }
    }
    for (int j = 0; j < (SPEED_OF_GAME * PRODUCT_FACTOR_GRAVITY) + ADD_FACTOR_GRAVITY; j++) {
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

void Game::reset_death_sound(){
    for (auto it = ducks_states.begin(); it != ducks_states.end(); ++it) {
        it->second->do_death_sound = true;
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
    snapshot.sounds = this->map.get_sounds_DTO();
    for (auto it = ducks_states.begin(); it != ducks_states.end(); ++it) {
        // if(it->second->is_dea
        if (!this->map.duck_is_alive(it->first) && this->ducks_states[it->first]->do_death_sound) {
            std::cout << "Duck " << it->first << " is dead" << std::endl;
            std::cout << "do death sound " << this->ducks_states[it->first]->do_death_sound << std::endl;
            snapshot.sounds.death = true;
            this->ducks_states[it->first]->do_death_sound = false;
            std::cout << "do death sound ahora es: " << this->ducks_states[it->first]->do_death_sound << std::endl;
            
            break;
        }
    }
    return snapshot;
}

map_structure_t Game::get_map_structure() {
    map_structure_t map_structure;
    map_structure.height = this->map.get_height();
    map_structure.width = this->map.get_width();
    map_structure.platforms = this->map.get_platforms_DTO();
    map_structure.platforms_len = static_cast<uint16_t>(map_structure.platforms.size());
    map_structure.spawns_platforms = this->map.get_weapon_spawn_positions_DTO();
    map_structure.spawns_platforms_len = static_cast<uint16_t>(map_structure.spawns_platforms.size());
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
        this->map.use_item(id, this->ducks_states[id]->facing_direction, false,
                           this->ducks_states[id]->looking_up);
    }
}

void Game::crouch_duck(int id, bool crouch) {
    if (crouch && this->map.duck_is_alive(id)) {
        this->ducks_states[id]->crouching = true;
        this->map.crouch_duck(id, true);
    }
}

void Game::stop_crouch_duck(int id, bool stop_crouch) {
    if (stop_crouch && this->map.duck_is_alive(id)) {
        this->ducks_states[id]->trying_to_stand = true;
    }
}

void Game::keep_using_item() {
    std::vector<int> ducks_id = this->map.get_live_duck_ids();
    for (auto& id: ducks_id) {
        this->map.continue_fire_rate(id, SPEED_OF_GAME);
        if (this->ducks_states[id]->holding_action) {
            this->map.use_item(id, this->ducks_states[id]->facing_direction, true,
                               this->ducks_states[id]->looking_up);
        }
    }
}

void Game::add_spawn_duck(Hitbox hitbox) {
        this->spawn_ducks.push_back(std::make_tuple(hitbox.get_x(), hitbox.get_y()));
}

void Game::add_spawn_position(Hitbox hitbox) {
        this->spawn_positions.push_back(std::make_tuple(hitbox.get_x(), hitbox.get_y()-26));
        this->map.add_weapon_spawn_position(hitbox);
}

void Game::stop_duck_item(int id, bool stop_fire) {
    if (stop_fire) {
        this->ducks_states[id]->holding_action = false;
        return;
    }
}

void Game::duck_looks_up(int id, bool looking_up) {
    if (looking_up) {
        this->ducks_states[id]->looking_up = true;
        return;
    }
}

void Game::duck_stops_looking_up(int id, bool stops_looking_up) {

    if (stops_looking_up) {
        this->ducks_states[id]->looking_up = false;
        return;
    }
}

void Game::pick_up_item(int duck_id, bool pick_up) {
    if (!pick_up || !this->map.duck_exist(duck_id) || !this->map.duck_is_alive(duck_id)) {
        return;
    }
    this->map.ducks_try_throw(duck_id, this->ducks_states[duck_id]->facing_direction);
}

void Game::throw_item(int id, bool throw_item) {
    if (!throw_item || !this->map.duck_exist(id) || !this->map.duck_is_alive(id)) {
        return;
    }
    this->map.throw_item(id, this->ducks_states[id]->facing_direction,
                         this->ducks_states[id]->looking_up);
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
        reset_death_sound();
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

void Game::random_item_spawn(bool on_game, bool lineal_spawn) {
    if (on_game && this->time_to_respawn > 0) {
        this->time_to_respawn -= 1;
        return;
    }
    std::string mode = "random";
    if(lineal_spawn){
        mode = "lineal";
    }
    for (auto& pos: this->spawn_positions) {
        if (this->map.already_exist_a_pickable(std::get<X_POSITION>(pos),
                                               std::get<Y_POSITION>(pos), WEAPON_SPAWN_SIZE, WEAPON_SPAWN_SIZE)) {
            continue;
        } else {
            try {
                this->map.add_item(WeaponFactory::createWeapon(this->map.get_bullets_list(),
                                                               mode, this->weapons_config),
                                   std::get<X_POSITION>(pos), std::get<Y_POSITION>(pos));
            } catch (MapError& e) {
                std::cerr << e.what() << std::endl;
                std::cerr << "Error al agregar arma en modo " << mode << " en posicion ("
                          << std::get<X_POSITION>(pos) << " " << std::get<Y_POSITION>(pos) << ") "
                          << std::endl;
                continue;
            }
        }
    }
    this->time_to_respawn = TIME_TO_RESPAWN;
}

// preguntar por esto
void Game::reset_round() {
    this->map.clean_map(this->spawn_ducks);
    this->actual_round += 1;
    for (auto& pos: this->spawn_positions) {
        this->random_item_spawn(false, false);
    }
}

void Game::load_configuration(GameConfig& config) {
    std::vector<std::tuple<int, int, int, int>> aux_tuple = config.get_item("platforms");
    // platforms
    this->load_platforms(aux_tuple);
    // boxes
    aux_tuple = config.get_item("boxes");
    this->load_boxes(aux_tuple);
    // ducks
    aux_tuple = config.get_item("ducks_spawn");
    this->load_spawn_ducks(aux_tuple);
    // weapons
    aux_tuple = config.get_item("weapons_spawn");
    this->load_spawn_weapons(aux_tuple);
}