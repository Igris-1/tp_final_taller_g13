#include "game.h"
#include <algorithm> 
#ifndef NUEVO_MAPA
// Game::Game(int height, int width): map(width, height), ducks_states(), ducks() {}

// void Game::duck_exist(int id) {
//     if (this->ducks.find(id) == this->ducks.end()) {
//         throw GameError("Duck id error");
//     }
//     return;
// }

// int Game::add_duck(int health, int id) {
//     if (this->ducks.find(id) != this->ducks.end()) {
//         throw GameError("Duck id already exists");
//     }
//     std::shared_ptr<Duck> new_duck = std::make_shared<Duck>(health, id);
//     this->ducks[id] = new_duck;
//     ducks_states.emplace(id, std::make_shared<duck_state>());
//     return id;
// }

// void Game::remove_duck(int id) {
//     this->duck_exist(id);
//     this->ducks.erase(id);
//     this->ducks_states.erase(id);
// }

// void Game::run_duck(int duck_id, bool left, bool right) {
//     this->duck_exist(duck_id);
//     if (!this->ducks[duck_id]->is_alive()) {
//         return;
//     }
//     if (!this->ducks_states[duck_id]->is_moving_left) {
//         this->ducks_states[duck_id]->is_moving_left = left;
//     }
//     if (!this->ducks_states[duck_id]->is_moving_right) {
//         this->ducks_states[duck_id]->is_moving_right = right;
//     }
// }

// void Game::pick_up_item(int id, bool pick_up) {
//     this->duck_exist(id);
//     if (pick_up) {
//         int i = 0;
//         bool picked_up = false;
//         size_t size = weapons_on_map.size();
//         std::cout << "size es: " << size << std::endl;
//         for (auto it = weapons_on_map.begin(); it != weapons_on_map.end();) {
//             if (ducks[id]->get_hitbox().has_collision((*it)->get_hitbox())) {
//                 std::cout << "chequeo 1 posicion: " << i << std::endl;
//                 picked_up = true;
//                 std::shared_ptr<Weapon> other_weapon = ducks[id]->take_weapon(*it);
//                 std::cout << "chequeo 2" << std::endl;
//                 if (other_weapon != nullptr) {
//                     std::cout << "chequeo 3" << std::endl;
//                     other_weapon->move_to((*it)->get_x(), (*it)->get_y());
//                     other_weapon->set_falling(true);
//                     std::cout << "chequeo 4 x es: " << (*it)->get_x() << "y es: " << (*it)->get_y()
//                               << std::endl;
//                     weapons_on_map.push_back(other_weapon);
//                     std::cout << "chequeo 5" << std::endl;
//                 }
//                 it = weapons_on_map.erase(it);
//                 break;
//             }
//             ++it;
//             i++;
//         }
//         if (ducks[id]->has_weapon() && !picked_up) {
//             std::cout << "tiro arma desp d chequear en pos " << i << std::endl;
//             std::shared_ptr<Weapon> weapon = ducks[id]->throw_weapon();
//             if (weapon == nullptr) {
//                 return;
//             } else {
//                 std::cout << "devolvio un arma" << std::endl;
//             }
//             weapon->move_to(ducks[id]->get_x(), ducks[id]->get_y());
//             if (ducks_states[id]->facing_direction) {
//                 std::cout << "tiro a la der" << std::endl;
//                 weapon->set_direction(1, -1);
//             } else {
//                 std::cout << "tiro a la izq" << std::endl;
//                 weapon->set_direction(-1, -1);
//             }
//             weapons_on_map.push_back(weapon);
//             return;
//         }
//     }
// }

// void Game::set_duck_start_position(int id, int x, int y) {
//     this->duck_exist(id);
//     if (!this->map.set_duck_start_position(this->ducks[id], x, y)) {
//         throw GameError("Duck start position is invalid");
//     }
// }

// std::vector<duck_DTO> Game::get_duck_DTO_list() {
//     std::vector<duck_DTO> list_DTO;
//     for (auto it = this->ducks.begin(); it != this->ducks.end(); it++) {

//         duck_DTO new_dto = it->second->to_DTO();
//         new_dto.is_moving_left = this->ducks_states[it->first]->is_moving_left;
//         new_dto.is_moving_right = this->ducks_states[it->first]->is_moving_right;

//         new_dto.jumping = this->ducks_states[it->first]->is_jumping;
//         new_dto.falling = this->ducks_states[it->first]->is_falling;
//         new_dto.is_alive = it->second->is_alive();
//         // new_dto.shooting = this->ducks_states[it->first].is_shooting;
//         list_DTO.push_back(new_dto);
//     }
//     return list_DTO;
// }

// std::vector<bullet_DTO> Game::get_bullet_DTO_list() {
//     std::vector<bullet_DTO> list_DTO;
//     for (auto it = this->bullets.begin(); it != this->bullets.end(); it++) {
//         bullet_DTO new_dto = (*it)->to_DTO();
//         list_DTO.push_back(new_dto);
//     }
//     return list_DTO;
// }

// std::vector<weapon_DTO> Game::get_weapon_DTO_list() {
//    return this->map.get_weapons_DTO_list(); 
// }

// void Game::respawner() {
//     for (auto it = this->ducks.begin(); it != this->ducks.end(); it++) {
//         if (!it->second->is_alive() && it->second->get_respawn_time() == 0) {
//             it->second->set_health(100);
//         } else if (!it->second->is_alive()) {
//             it->second->tick_respawn_time();
//         }
//     }
// }

// void Game::continue_horizontal_movements(int count) {

//     for (int i = 0; i < count; i++) {
//         for (auto it = this->ducks.begin(); it != this->ducks.end(); it++) {
//             if (!it->second->is_alive()) {
//                 continue;
//             }
//             // se mueve para la left si is_moving_left is true
//             if (this->ducks_states[it->first]->is_moving_left) {
//                 this->ducks_states[it->first]->facing_direction = false;
//                 if (this->map.can_move_hitbox(it->second->get_hitbox(), LEFT_MOVEMENT, 0)) {
//                     it->second->move_relative_to(LEFT_MOVEMENT, 0);
//                 }
//             }
//             // se mueve para la right si is_moving_right is true
//             if (this->ducks_states[it->first]->is_moving_right) {
//                 this->ducks_states[it->first]->facing_direction = true;
//                 if (this->map.can_move_hitbox(it->second->get_hitbox(), RIGHT_MOVEMENT, 0)) {
//                     it->second->move_relative_to(RIGHT_MOVEMENT, 0);
//                 }
//             }
//         }
//     }
//     for (int j = 0; j < count * 4; j++) {
//         for (auto it = bullets.begin(); it != bullets.end();) {
//             if ((*it)->next_position(this->map)) {
//                 for (auto& duck: this->ducks) {
//                     if (duck.second->get_hitbox().has_collision((*it)->get_hitbox())) {
//                         std::cout << "calculo danio" << std::endl;
//                         int numerito = (*it)->damage_generated(duck.second->get_id());
//                         std::cout << "recibe danio" << std::endl;
//                         duck.second->receive_damage(numerito);
//                         std::cout << "recibio danio" << std::endl;
//                         break;
//                     }
//                 }
//                 ++it;
//             } else {
//                 it = bullets.erase(it);
//             }
//         }
//     }


//     for (int j = 0; j < (count * 3); j++) {
//         for (auto it = weapons_on_map.begin(); it != weapons_on_map.end();) {
//             if ((*it)->is_moving() && (*it)->get_x_direction() > 0 &&
//                 this->map.can_move_hitbox((*it)->get_hitbox(), RIGHT_MOVEMENT, 0)) {
//                 (*it)->air_time_down_x();
//                 (*it)->move_relative_to(RIGHT_MOVEMENT, 0);
//             } else if ((*it)->is_moving() && (*it)->get_x_direction() < 0 &&
//                        this->map.can_move_hitbox((*it)->get_hitbox(), LEFT_MOVEMENT, 0)) {
//                 (*it)->air_time_down_x();
//                 (*it)->move_relative_to(LEFT_MOVEMENT, 0);
//             }

//             ++it;
//         }
//     }
// }

// void Game::continue_vertical_movements(int count) {

//     for (auto it = this->ducks.begin(); it != this->ducks.end(); it++) {
//         if (this->ducks_states[it->first]->is_jumping) {
//             for (int i = 0; i < (count * PRODUCT_FACTOR_JUMP) + ADD_FACTOR_JUMP; i++) {
//                 if (this->ducks_states[it->first]->tiles_to_jump > 0) {
//                     // this->map.move_duck(it->second, 0, JUMP_DIRECTION);
//                     if (this->map.can_move_hitbox(it->second->get_hitbox(), 0, JUMP_DIRECTION)) {
//                         it->second->move_relative_to(0, JUMP_DIRECTION);
//                     }
//                     this->ducks_states[it->first]->tiles_to_jump--;
//                 }
//                 if (this->ducks_states[it->first]->tiles_to_jump == 0) {
//                     this->ducks_states[it->first]->air_time--;
//                 }
//                 if (this->ducks_states[it->first]->tiles_to_jump == 0 &&
//                     this->ducks_states[it->first]->air_time == 0) {
//                     this->ducks_states[it->first]->is_jumping = false;
//                     this->ducks_states[it->first]->is_falling = true;
//                 }
//             }
//         } else if (this->ducks_states[it->first]->falling_with_style) {
//             for (int i = 0; i < (count) + ADD_FACTOR_GRAVITY; i++) {
//                 if (this->ducks_states[it->first]->falling_with_style && i % 2 == 0) {  //
//                     //    this->ducks_states[it->first]->is_falling =
//                     //    this->map.move_duck(it->second, 0, GRAVITY);
//                     if (this->map.can_move_hitbox(it->second->get_hitbox(), 0, GRAVITY)) {
//                         it->second->move_relative_to(0, GRAVITY);
//                         this->ducks_states[it->first]->is_falling = true;
//                     } else {
//                         this->ducks_states[it->first]->is_falling = false;
//                     }
//                 }
//             }
//         } else {
//             for (int i = 0; i < (count * PRODUCT_FACTOR_GRAVITY) + ADD_FACTOR_GRAVITY; i++) {
//                 // this->ducks_states[it->first]->is_falling = this->map.move_duck(it->second, 0,
//                 // GRAVITY);
//                 if (this->map.can_move_hitbox(it->second->get_hitbox(), 0, GRAVITY)) {
//                     it->second->move_relative_to(0, GRAVITY);
//                     this->ducks_states[it->first]->is_falling = true;
//                 } else {
//                     this->ducks_states[it->first]->is_falling = false;
//                 }
//             }
//         }
//     }

//     for (auto it = weapons_on_map.begin(); it != weapons_on_map.end();) {
//         for (int j = 0; j < (count * PRODUCT_FACTOR_GRAVITY) + ADD_FACTOR_GRAVITY; j++) {
//             (*it)->air_time_down_y();
//             if (!(*it)->is_falling() &&
//                 this->map.can_move_hitbox((*it)->get_hitbox(), 0, JUMP_DIRECTION)) {  //

//                 (*it)->move_relative_to(0, JUMP_DIRECTION);
//                 continue;
//             }
//             if ((*it)->is_falling() && this->map.can_move_hitbox((*it)->get_hitbox(), 0, GRAVITY)) {

//                 (*it)->move_relative_to(0, GRAVITY);
//             }
//         }
//         ++it;
//     }
// }


// void Game::stop_run_duck(int id, bool stop_left, bool stop_right) {
//     this->duck_exist(id);
//     if (stop_left) {
//         this->ducks_states[id]->is_moving_left = !stop_left;
//     }
//     if (stop_right) {
//         this->ducks_states[id]->is_moving_right = !stop_right;
//     }
// }

// // Position Game::position_duck(int id) {
// //     this->duck_exist(id);
// //     return this->ducks[id]->get_position();
// // }

// game_snapshot_t Game::get_snapshot() {
//     game_snapshot_t snapshot;
//     snapshot.ducks_len = this->ducks.size();
//     snapshot.ducks = this->get_duck_DTO_list();
//     snapshot.bullets_len = this->bullets.size();
//     snapshot.bullets = this->get_bullet_DTO_list();
//     snapshot.weapons = this->get_weapon_DTO_list();
//     snapshot.weapons_len = snapshot.weapons.size();
//     std::cout << "snapshot weapons len: " << snapshot.weapons_len << std::endl;
//     std::cout << "snapshot weapons len: " << snapshot.weapons.size() << std::endl;
//     return snapshot;
// }

// map_structure_t Game::get_map_structure() {
//     map_structure_t map_structure;
//     map_structure.platforms = this->map.get_platforms_DTO();
//     map_structure.platforms_len = static_cast<uint16_t>(map_structure.platforms.size());
//     return map_structure;
// }

// void Game::jump_duck(int id, bool jump) {
//     if (!this->ducks[id]->is_alive()) {
//         return;
//     }
//     this->duck_exist(id);
//     if (jump) {
//         this->ducks_states[id]->falling_with_style = true;
//     }
//     if (!this->ducks_states[id]->is_jumping && jump &&
//         !this->ducks_states[id]->is_falling) {  // esto no es suficiente para evitar que vuele

//         this->ducks_states[id]->is_jumping = true;
//         this->ducks_states[id]->tiles_to_jump = TILES_FOR_JUMP;
//         this->ducks_states[id]->air_time = 40;
//     }
//     if (jump && this->ducks_states[id]->is_falling) {
//         this->ducks_states[id]->falling_with_style = true;
//     }
// }

// void Game::stop_jump_duck(int id, bool stop_jump) {
//     if (stop_jump) {
//         this->ducks_states[id]->falling_with_style = false;
//     }
// }

// void Game::fire_duck_weapon(int id, bool fire) {
//     if (fire && this->ducks[id]->is_alive()) {
//         this->ducks_states[id]->is_shooting = true;
//     }
// }

// void Game::keep_shooting() {

//     for (auto it = this->ducks.begin(); it != this->ducks.end(); it++) {
//         it->second->continue_fire_rate();
//         std::vector<std::shared_ptr<BulletInterface>> new_bullets;
//         if (this->ducks_states[it->first]->is_shooting &&
//             this->ducks_states[it->first]->facing_direction) {
//             // new_bullets = it->second->fire_weapon(1, 0, this->map);
//             it->second->use_item(1, 0, this->map);
//         }
//         if (this->ducks_states[it->first]->is_shooting &&
//             !this->ducks_states[it->first]->facing_direction) {
//             // new_bullets = it->second->fire_weapon(-1, 0, this->map);
//             it->second->use_item(-1, 0, this->map);
//         }
//         // int size = new_bullets.size();
//         // for(int i = 0; i < size; i++){
//         //     this->bullets.push_back(new_bullets[i]);
//         // }
//     }
// }

// void Game::stop_duck_weapon(int id, bool stop_fire) {
//     if (stop_fire) {
//         this->ducks_states[id]->is_shooting = false;
//         return;
//     }
// }

// void Game::add_invalid_position(Hitbox hitbox) {
//     if (!this->map.add_invalid_position(hitbox)) {
//         throw GameError("game can't add invalid position");
//     }
// }

// void Game::add_new_platform(Hitbox hitbox) {
//     if (!this->map.add_platform(hitbox)) {
//         throw GameError("game can't add invalid position");
//     }
// }

// // void Game::add_weapon_on_map(std::string type_weapon, int x, int y) {
// //     std::shared_ptr<Weapon> weapon =
// //             std::make_shared<Weapon>(WeaponFactory::createWeapon(this->bullets, type_weapon));
// //     if (!this->map.can_move_hitbox(weapon->get_hitbox(), x, y)) {
// //         throw GameError("game can't add weapon to map");
// //     }
// //     weapon->move_to(x, y);
// //     this->weapons_on_map.push_back(weapon);
// // }

#endif


/* --------- NUEVOOO GAMEEEE----------------------------------------------------------------------------------------------------------------------------------------v------*/
#ifdef NUEVO_MAPA

Game::Game(int height, int width): map(width, height), ducks_states() {}

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
    }
}

std::vector<duck_DTO> Game::get_duck_DTO_list() {
    std::vector<duck_DTO> list_DTO = this->map.get_duck_DTO_list();
    for (auto& it: list_DTO) {
        it.is_moving_left = this->ducks_states[it.duck_id]->is_moving_left;
        it.is_moving_right = this->ducks_states[it.duck_id]->is_moving_right;
        it.jumping = this->ducks_states[it.duck_id]->is_jumping;
        it.falling = this->ducks_states[it.duck_id]->is_falling;
        // it.shooting = this->ducks_states[it.duck_id].is_shooting;
    }
    return list_DTO;
}

score_DTO Game::get_score_DTO(){

    score_DTO score;
    
    std::vector<std::pair<int, int>> sorted_ducks(this->ducks_score.begin(), this->ducks_score.end());

    std::sort(sorted_ducks.begin(), sorted_ducks.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; 
    });

    if (!sorted_ducks.empty()) {
        score.first_place_id = sorted_ducks[0].first;
        std::cout << "first place id score: " << sorted_ducks[0].second << std::endl;
        score.first_place_score = sorted_ducks[0].second;
        std::cout << "first place en struct: " << static_cast<int>(score.first_place_score) << std::endl;
    }
    if (sorted_ducks.size() > 1) {
        score.second_place_id = sorted_ducks[1].first;
        std::cout << "second place id: " << sorted_ducks[1].first << std::endl;
        score.second_place_score = sorted_ducks[1].second;
        std::cout << "second place en struct: " << static_cast<int>(score.second_place_score) << std::endl;
    }
    if (sorted_ducks.size() > 2) {
        score.third_place_id = sorted_ducks[2].first;
        std::cout << "third place id: " << sorted_ducks[2].first << std::endl;
        score.third_place_score = sorted_ducks[2].second;
        std::cout << "third place en struct: " << static_cast<int>(score.third_place_score) << std::endl;
    }
    if (sorted_ducks.size() > 3) {
        score.fourth_place_id = sorted_ducks[3].first;
        std::cout << "fourth place id: " << sorted_ducks[3].first << std::endl;
        score.fourth_place_score = sorted_ducks[3].second;
        std::cout << "fourth place en struct: " << static_cast<int>(score.fourth_place_score) << std::endl;
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
    // for(int j=0; j< (count * 3); j++){
    //         for (auto it = weapons_on_map.begin(); it != weapons_on_map.end(); ) {
    //             if((*it)->is_moving() && (*it)->get_x_direction() > 0 &&
    //             this->map.can_move_hitbox((*it)->get_hitbox(),RIGHT_MOVEMENT,0)){
    //                 (*it)->air_time_down_x();
    //                 (*it)->move_relative_to(RIGHT_MOVEMENT, 0);
    //             }
    //             else if((*it)->is_moving() && (*it)->get_x_direction() < 0 &&
    //             this->map.can_move_hitbox((*it)->get_hitbox(),LEFT_MOVEMENT, 0)){
    //                 (*it)->air_time_down_x();
    //                 (*it)->move_relative_to(LEFT_MOVEMENT,0);
    //             }

    //             ++it;
    //         }
    // }
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

    for(int j=0; j< (count * PRODUCT_FACTOR_GRAVITY) + ADD_FACTOR_GRAVITY; j++){
        this->map.gravity_weapon();
    }
    // for(int j=0; j< (count * PRODUCT_FACTOR_GRAVITY) + ADD_FACTOR_GRAVITY; j++){
    //   for (auto it = weapons_on_map.begin(); it != weapons_on_map.end(); ){

    // for (auto it = weapons_on_map.begin(); it != weapons_on_map.end(); ){
    //  for(int j=0; j< (count * PRODUCT_FACTOR_GRAVITY) + ADD_FACTOR_GRAVITY; j++){
    //         (*it)->air_time_down_y();
    //         if(!(*it)->is_falling() && this->map.can_move_hitbox((*it)->get_hitbox(),0,
    //         JUMP_DIRECTION)){//

    //             (*it)->move_relative_to(0, JUMP_DIRECTION);
    //             continue;
    //         }
    //         if((*it)->is_falling() && this->map.can_move_hitbox((*it)->get_hitbox(),0, GRAVITY)){
    //             std::cout << "se cae" << std::endl;
    //             (*it)->move_relative_to(0, GRAVITY);
    //         }
    //     }
    //     ++it;
    // }
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

void Game::fire_duck_weapon(int id, bool fire) {
    if (fire && this->map.duck_is_alive(id)) {
        this->ducks_states[id]->is_shooting = true;
    }
}

void Game::keep_shooting() {
    std::vector<int> ducks_id = this->map.get_live_duck_ids();
    for (auto& id: ducks_id) {
        this->map.continue_fire_rate(id);
        if (this->ducks_states[id]->is_shooting) {
            this->map.use_item(id, this->ducks_states[id]->facing_direction);
        }
    }
}

void Game::add_spawn_position(int x, int y){
    this->spawn_positions.push_back(std::make_tuple(x, y));
}

void Game::stop_duck_weapon(int id, bool stop_fire) {
    if (stop_fire) {
        this->ducks_states[id]->is_shooting = false;
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
        throw GameError("game can't add invalid position");
    }
}

void Game::add_weapon_on_map(std::string type_weapon, int x, int y) {
    std::shared_ptr<Weapon> weapon =
    std::make_shared<Weapon>(WeaponFactory::createWeapon(this->map.get_bullets_list(), type_weapon));
    this->map.add_weapon(weapon, x, y);
}

void Game::pick_up_item(int duck_id, bool pick_up) {
    if (!pick_up || !this->map.duck_exist(duck_id) || !this->map.duck_is_alive(duck_id)) {
        return;
    }  
    this->map.ducks_try_throw(duck_id, this->ducks_states[duck_id]->facing_direction);
}

void Game::start_game(){
    this->started_game = true;
    this->actual_round += 1;
    std::vector<int> ids_ducks = this->map.get_live_duck_ids();
    for (auto& id: ids_ducks){
        this->ducks_score[id] = 0;
    }
}
bool Game::check_if_round_finished(){    
    std::vector<int> ids_ducks = this->map.get_live_duck_ids();
    int dead_ducks = this->map.ducks_dead_size();
    if(ids_ducks.size() <= 1 && dead_ducks > 0){
        if(ids_ducks.size() == 1){
            this->ducks_score[ids_ducks[0]] += 1;
            std::cout << "Duck id: " << ids_ducks[0] << " score: " << this->ducks_score[ids_ducks[0]] << std::endl;
        }
        return true;
    }
    return false;
}

bool Game::check_if_winner(){
    for (auto it = ducks_score.begin(); it != ducks_score.end(); ++it) {
        if(it->second == 10){
            return true;
        }
    }  
    return false;
}

void Game::random_weapon_spawn(){
    for(auto& pos: this->spawn_positions){
        if(this->map.already_exist_a_pickable(std::get<0>(pos), std::get<1>(pos))){
            continue;
        }else{
            this->map.add_weapon(std::make_shared<Weapon>(WeaponFactory::createWeapon(this->map.get_bullets_list(), "random")), std::get<0>(pos), std::get<1>(pos));
        }
    }
}

void Game::reset_round(){
    this->map.clean_map();
    this->actual_round += 1;
    for(auto& pos: this->spawn_positions){
        random_weapon_spawn();
        //this->map.add_weapon(std::make_shared<Weapon>(WeaponFactory::createWeapon(this->map.get_bullets_list(), "random")), std::get<0>(pos), std::get<1>(pos));
    }
}

#endif
