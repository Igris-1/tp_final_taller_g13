#define NUEVO_MAPA  
#include "map_game.h"

#include <iostream>


#ifndef NUEVO_MAPA
MapGame::MapGame(int width, int height): height(height), width(width) {}

bool MapGame::hitbox_in_range(Hitbox hitbox) {
    int hitbox_left = hitbox.get_x();
    int hitbox_right = hitbox.get_x() + hitbox.get_width();
    int hitbox_top = hitbox.get_y();
    int hitbox_bottom = hitbox.get_y() + hitbox.get_height();

    return (hitbox_left >= 0 && hitbox_right <= this->width && hitbox_top >= 0 &&
            hitbox_bottom <= this->height);
}

bool MapGame::not_in_invalid_position(Hitbox hitbox) {
    for (Hitbox invalid_position: this->invalid_positions) {
        if (invalid_position.has_collision(hitbox)) {
            return false;
        }
    }
    return true;
}

bool MapGame::not_in_platforms(Hitbox hitbox) {
    for (Hitbox platform: this->platforms) {
        if (platform.has_collision(hitbox)) {
            return false;
        }
    }
    return true;
}

bool MapGame::position_is_valid(Hitbox hitbox) {
    if (!hitbox_in_range(hitbox)) {
        return false;
    }
    return not_in_invalid_position(hitbox) && not_in_platforms(hitbox);
}

bool MapGame::add_invalid_position(Hitbox hitbox) {
    if (!hitbox_in_range(hitbox) && not_in_platforms(hitbox)) {
        return false;
    }
    this->invalid_positions.insert(hitbox);
    return true;
}

bool MapGame::add_platform(Hitbox hitbox) {
    if (!hitbox_in_range(hitbox) && not_in_invalid_position(hitbox)) {
        // std::cout << "hubo un false" << std::endl;
        return false;
    }
    this->platforms.insert(hitbox);
    return true;
}


bool MapGame::move_duck(std::shared_ptr<Duck> duck, int dx, int dy) {
    Hitbox aux = duck->get_hitbox();
    aux.move_relative(dx, dy);
    if (position_is_valid(aux)) {
        duck->move_relative_to(dx, dy);
        return true;
    }
    return false;
}

// bool MapGame::move_bullet(BulletInterface* bullet, int dx, int dy){
//     Hitbox aux = bullet->get_hitbox();
//     aux.move_relative(dx, dy);
//         if(position_is_valid(aux)){
//             bullet->move_relative_to(dx, dy);
//             return true;
//         }
//     return false;
// }

bool MapGame::can_move_hitbox(Hitbox hitbox, int dx, int dy) {
    hitbox.move_relative(dx, dy);
    if (position_is_valid(hitbox)) {
        return true;
    }
    return false;
}

bool MapGame::set_duck_start_position(std::shared_ptr<Duck> duck, int x, int y) {
    Hitbox aux = duck->get_hitbox();
    aux.move(x, y);
    if (!position_is_valid(aux)) {
        return false;
    }
    duck->move_to(x, y);
    return true;
}


std::vector<platform_DTO> MapGame::get_platforms_DTO() {
    std::vector<platform_DTO> vector_platforms;
    vector_platforms.resize(0);
    for (Hitbox p: this->platforms) {
        platform_DTO dto = {static_cast<uint16_t>(p.get_x()), static_cast<uint16_t>(p.get_y()),
                            static_cast<uint16_t>(p.get_width()),
                            static_cast<uint16_t>(p.get_height())};
        vector_platforms.push_back(dto);
    }
    return vector_platforms;
}


#endif

/*------NUEVOOOOOOOOOOOO -----------------------------------------------------------------
-------------------------MAPAAAAAAAA ---------------------------------------------------*/

#ifdef NUEVO_MAPA

MapGame::MapGame(int width, int height): height(height), width(width) {}

bool MapGame::duck_exist(int id) { return this->ducks.find(id) != this->ducks.end(); }

bool MapGame::not_in_invalid_position(Hitbox hitbox) {
    for (Hitbox invalid_position: this->invalid_positions) {
        if (invalid_position.has_collision(hitbox)) {
            return false;
        }
    }
    return true;
}

bool MapGame::not_in_platforms(Hitbox hitbox) {
    for (Hitbox platform: this->platforms) {
        if (platform.has_collision(hitbox)) {
            return false;
        }
    }
    return true;
}

bool MapGame::hitbox_in_range(Hitbox hitbox) {
    int hitbox_left = hitbox.get_x();
    int hitbox_right = hitbox.get_x() + hitbox.get_width();
    int hitbox_top = hitbox.get_y();
    int hitbox_bottom = hitbox.get_y() + hitbox.get_height();

    return (hitbox_left >= 0 && hitbox_right <= this->width && hitbox_top >= 0 &&
            hitbox_bottom <= this->height);
}

bool MapGame::position_is_valid(Hitbox hitbox) {
    if (!hitbox_in_range(hitbox)) {
        return false;
    }
    return not_in_invalid_position(hitbox) && not_in_platforms(hitbox);
}

bool MapGame::set_duck_start_position(int id, int x, int y) {
    if (this->ducks.find(id) != this->ducks.end()) {
        throw MapError("Duck id already exists");
    }
    std::shared_ptr<Duck> new_duck = std::make_shared<Duck>(HEALTH, id);
    this->ducks[id] = new_duck;
    Hitbox aux = new_duck->get_hitbox();
    aux.move(x, y);
    if (!position_is_valid(aux)) {
        return false;
    }
    new_duck->move_to(x, y);
    return true;
}

std::vector<duck_DTO> MapGame::get_duck_DTO_list() {
    std::vector<duck_DTO> list_DTO;
    for (auto it = this->ducks.begin(); it != this->ducks.end(); it++) {
        duck_DTO new_dto = it->second->to_DTO();
        new_dto.is_alive = it->second->is_alive();
        list_DTO.push_back(new_dto);
    }
    return list_DTO;
}

std::vector<weapon_DTO> MapGame::get_weapons_DTO_list(){
    std::vector<weapon_DTO> list_DTO;
    for (auto it = this->pickables.begin(); it != this->pickables.end(); it++) {
        weapon_DTO new_dto = (*it)->to_DTO();
        list_DTO.push_back(new_dto);
    }
    return list_DTO;
}

bool MapGame::duck_is_alive(int id) {
    if (this->ducks.find(id) == this->ducks.end()) {
        throw MapError("El pato no existe");
    }
    return this->ducks[id]->is_alive();
}

bool MapGame::add_invalid_position(Hitbox hitbox) {
    if (!hitbox_in_range(hitbox) && not_in_platforms(hitbox)) {
        return false;
    }
    this->invalid_positions.insert(hitbox);
    return true;
}

bool MapGame::add_platform(Hitbox hitbox) {
    if (!hitbox_in_range(hitbox) && not_in_invalid_position(hitbox)) {
        // std::cout << "hubo un false" << std::endl;
        return false;
    }
    this->platforms.insert(hitbox);
    return true;
}

bool MapGame::can_move_hitbox(Hitbox hitbox, int dx, int dy) {
    hitbox.move_relative(dx, dy);
    if (position_is_valid(hitbox)) {
        return true;
    }
    return false;
}

bool MapGame::move_relative_if_posible(int duck_id, int dx, int dy) {
    auto duck = this->ducks[duck_id];
    int x_step = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
    int y_step = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;

    int remaining_dx = std::abs(dx);
    int remaining_dy = std::abs(dy);

    while (remaining_dx > 0 || remaining_dy > 0) {
        int step_dx = (remaining_dx > 0) ? x_step : 0;
        int step_dy = (remaining_dy > 0) ? y_step : 0;

        if (can_move_hitbox(duck->get_hitbox(), step_dx, step_dy)) {
            duck->move_relative_to(step_dx, step_dy);
        } else {
            return false;
        }

        remaining_dx -= std::abs(step_dx);
        remaining_dy -= std::abs(step_dy);
    }

    return true;
}

void MapGame::respawn_ducks() {
    for (auto it = this->ducks.begin(); it != this->ducks.end(); it++) {
        if (!it->second->is_alive() && it->second->get_respawn_time() == 0) {
            it->second->set_health(100);
        } else if (!it->second->is_alive()) {
            it->second->tick_respawn_time();
        }
    }
}

std::vector<int> MapGame::get_live_duck_ids() {
    std::vector<int> live_duck_ids;
    for (auto it = this->ducks.begin(); it != this->ducks.end(); it++) {
        if (it->second->is_alive()) {
            live_duck_ids.push_back(it->first);
        }
    }
    return live_duck_ids;
}

std::vector<int> MapGame::get_all_duck_ids() {
    std::vector<int> duck_ids;
    for (auto it = this->ducks.begin(); it != this->ducks.end(); it++) {
        duck_ids.push_back(it->first);
    }
    return duck_ids;
}

void MapGame::remove_duck(int id) {
    if (this->ducks.find(id) == this->ducks.end()) {
        return;
    }
    this->ducks.erase(id);
}

std::vector<platform_DTO> MapGame::get_platforms_DTO() {
    std::vector<platform_DTO> vector_platforms;
    vector_platforms.resize(0);
    for (Hitbox p: this->platforms) {
        platform_DTO dto = {static_cast<uint16_t>(p.get_x()), static_cast<uint16_t>(p.get_y()),
                            static_cast<uint16_t>(p.get_width()),
                            static_cast<uint16_t>(p.get_height())};
        vector_platforms.push_back(dto);
    }
    return vector_platforms;
}

std::vector<bullet_DTO> MapGame::get_bullets_DTO_list() {
    std::vector<bullet_DTO> list_DTO;
    for (auto it = this->bullets.begin(); it != this->bullets.end(); it++) {
        bullet_DTO new_dto = (*it)->to_DTO();
        list_DTO.push_back(new_dto);
    }
    return list_DTO;
}

void MapGame::continue_fire_rate(int id) {
    if (this->duck_exist(id)) {
        this->ducks[id]->continue_fire_rate();
    }
}

void MapGame::gravity_weapon(){
        for (auto it = pickables.begin(); it != pickables.end(); ++it){
        //  for(int j=0; j< (count * PRODUCT_FACTOR_GRAVITY) + ADD_FACTOR_GRAVITY; j++){
            (*it)->air_time_down_y();
            Hitbox& hitbox = (*it)->get_reference_hitbox();
            if(!(*it)->is_falling()){
                this->move_relative_if_posible(hitbox, 0 ,JUMP_DIRECTION);
                continue;
            }
            if((*it)->is_falling()){         
                this->move_relative_if_posible(hitbox, 0, GRAVITY);
            }
        }
}
void MapGame::inertia_weapon(){
        for (auto it = pickables.begin(); it != pickables.end(); ++it){
        //  for(int j=0; j< (count * PRODUCT_FACTOR_GRAVITY) + ADD_FACTOR_GRAVITY; j++){
            (*it)->air_time_down_x();
            Hitbox& hitbox = (*it)->get_reference_hitbox();
            if((*it)->is_moving() && (*it)->get_x_direction() > 0){
                this->move_relative_if_posible(hitbox, RIGHT_DIRECTION , 0);
                continue;
            }
            if((*it)->is_moving() && (*it)->get_x_direction() < 0){         
                this->move_relative_if_posible(hitbox, LEFT_DIRECTION, 0);
            }
        }
}




void MapGame::bullets_next_movement() {
    for (auto bullet = bullets.begin(); bullet != bullets.end();) {
        if ((*bullet)->next_position(*this)) {
            for (auto& [id, duck]: this->ducks) {
                if (duck->get_hitbox().has_collision((*bullet)->get_hitbox())) {
                    int damage = (*bullet)->damage_generated(id);
                    duck->receive_damage(damage);
                    break;
                }
            }
            ++bullet;
        } else {
            bullet = bullets.erase(bullet);
        }
    }
}


bool MapGame::move_relative_if_posible(Hitbox& hitbox, int dx, int dy) {
    int x_step = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
    int y_step = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;

    int remaining_dx = std::abs(dx);
    int remaining_dy = std::abs(dy);

    while (remaining_dx > 0 || remaining_dy > 0) {
        int step_dx = (remaining_dx > 0) ? x_step : 0;
        int step_dy = (remaining_dy > 0) ? y_step : 0;

        if (can_move_hitbox(hitbox, step_dx, step_dy)) {
            hitbox.move_relative(step_dx, step_dy);
        } else {
            return false;
        }

        remaining_dx -= std::abs(step_dx);
        remaining_dy -= std::abs(step_dy);
    }

    return true;
}

void MapGame::use_item(int duck_id, bool right_direction) {
    if (!this->duck_exist(duck_id) || !this->duck_is_alive(duck_id)) {
        return;
    }
    if (right_direction) {
        this->ducks[duck_id]->use_item(RIGHT_DIRECTION, NO_DIRECTION, *this);
    } else {
        this->ducks[duck_id]->use_item(LEFT_DIRECTION, NO_DIRECTION, *this);
    }
}

// void MapGame::ducks_try_pick_up(int id_duck) {
//     std::shared_ptr<Duck> this_duck = this->ducks[id_duck];
//     std::cout << "entro a pick up de map2" << std::endl;
//     for (auto it = this->pickables.begin(); it != this->pickables.end();) {
//         std::cout << "entro a pick up de map3" << std::endl;
//         if (this_duck->get_hitbox().has_collision((*it)->get_hitbox())) {
//             std::cout << "entro a pick up de map4" << std::endl;
//             std::shared_ptr<Weapon> other_weapon = this_duck->take_weapon((*it));
//             if (other_weapon != nullptr) {
//                 other_weapon->move_to((*it)->get_x(), (*it)->get_y());
//                 pickables.push_back(other_weapon);
//             }
//             it = pickables.erase(it);
//             break;
//         }
//         ++it;
//     }
// }

void MapGame::ducks_try_throw(int id_duck, bool right_direction) {
    std::shared_ptr<Duck> this_duck = this->ducks[id_duck];
    bool weapon_picked_up = false;
    for (auto it = this->pickables.begin(); it != this->pickables.end();) {
        std::cout << "entro a pick up de map3" << std::endl;
        if (this_duck->get_hitbox().has_collision((*it)->get_hitbox())) {
            std::cout << "entro a pick up de map4" << std::endl;
            std::shared_ptr<Weapon> other_weapon = this_duck->take_weapon((*it));
            if (other_weapon != nullptr) {
                other_weapon->move_to((*it)->get_x(), (*it)->get_y());
                other_weapon->set_falling(true);
                other_weapon->set_moving(false);
                pickables.push_back(other_weapon);
            }
            it = pickables.erase(it);
            weapon_picked_up = true;
            break;
        }
        ++it;
    }
    if(weapon_picked_up){
        return;
    }
    if(this_duck->has_weapon()){
        std::shared_ptr<Weapon> weapon = this_duck->throw_weapon();
        if(weapon == nullptr){
            return;
        }
        weapon->move_to(this_duck->get_x(), this_duck->get_y());
        if(right_direction){
            weapon->set_direction(RIGHT_DIRECTION, JUMP_DIRECTION);
        }else{
            weapon->set_direction(LEFT_DIRECTION, JUMP_DIRECTION);
        }
        pickables.push_back(weapon);
    }
}

void MapGame::add_weapon(std::shared_ptr<Weapon> new_weapon, int x, int y){
    if (!this->can_move_hitbox(new_weapon->get_hitbox(), x, y)) {
        throw MapError("game can't add weapon to map");
    }
    new_weapon->move_to(x, y);
    this->pickables.push_back(new_weapon);
}

std::list<std::shared_ptr<BulletInterface>>& MapGame::get_bullets_list(){
    return this->bullets;
}
#endif