#include "map_game.h"

#include <iostream>

MapGame::MapGame(int width, int height): height(height), width(width) {}

bool MapGame::duck_exist(int id) { return this->ducks.find(id) != this->ducks.end(); }

bool MapGame::not_in_invalid_position(Hitbox hitbox, bool to_stand) {
    if(!to_stand){        
        for (Hitbox invalid_position: this->invalid_positions) {
            if (invalid_position.has_collision(hitbox)) {
                return false;
            }
        }
        return true;
    }
    for (Hitbox invalid_position: this->invalid_positions) {
        if (invalid_position.has_collision_above(hitbox)) {
            return false;
        }
    }
    return true;
}

bool MapGame::not_in_platforms(Hitbox hitbox, bool to_stand) {
    if(!to_stand){
        for (Hitbox platform: this->platforms) {
            if (platform.has_collision(hitbox)) {
                return false;
            }
        }
        return true;
    }
    for (Hitbox platform: this->platforms) {
            while(platform.has_collision_above(hitbox)){
                std::cout << "hitbox is trying to move up" << std::endl;
                if(!move_relative_if_posible(hitbox, 0, 1)){
                    return false;
                }
            }
        }
        return true;
}

bool MapGame::not_in_boxes(Hitbox hitbox, bool to_stand) {
    if(!to_stand){
        for (auto& box: this->boxes) {
            if (box->get_hitbox().has_collision(hitbox)) {
                return false;
            }
        }
        return true;
    }
    for (auto& box: this->boxes) {
        if (box->get_hitbox().has_collision_above(hitbox)) {
            return false;
        }
    }
    return true;
}

bool MapGame::out_of_map(Hitbox hitbox){
    return hitbox.get_y() >= this->height;
}

bool MapGame::hitbox_in_range(Hitbox hitbox, bool can_fall) {
    int hitbox_left = hitbox.get_x();
    int hitbox_right = hitbox.get_x() + hitbox.get_width();
    int hitbox_top = hitbox.get_y();
    int hitbox_bottom = hitbox.get_y() + hitbox.get_height();
    if (hitbox_left < 0 || hitbox_right > this->width || hitbox_top < 0) {
        return false;
    }
    if (!can_fall && hitbox_bottom > this->height) {
        return false;
    }
    return true;

}

bool MapGame::change_hitbox_size(Hitbox& hitbox, int width, int height, bool to_stand) {
    return hitbox.change_size(width, height, this->platforms);
}

bool MapGame::crouch_duck(int id, bool crouch){
    Hitbox& duck_hitbox = this->ducks[id]->get_hitbox_reference();
    if(!crouch){
    }
    if(crouch){
        return this->change_hitbox_size(duck_hitbox, DUCK_WIDTH, DUCK_CROUCH_HEIGHT, false);
    }
    return this->change_hitbox_size(duck_hitbox, DUCK_WIDTH, DUCK_HEIGHT, true);
}

bool MapGame::position_is_valid(Hitbox hitbox, bool can_fall, bool to_stand) {
    if (!hitbox_in_range(hitbox, can_fall)) {
        return false;
    }
    //return not_in_invalid_position(hitbox) && not_in_platforms(hitbox);

    bool uno = not_in_invalid_position(hitbox, to_stand);
    bool dos = not_in_platforms(hitbox, to_stand);

    return uno && dos;
}

bool MapGame::set_duck_start_position(int id, int x, int y) {
    if (this->ducks.find(id) != this->ducks.end()) {
        throw MapError("Duck id already exists");
    }
    std::shared_ptr<Duck> new_duck = std::make_shared<Duck>(HEALTH, id);
    this->ducks[id] = new_duck;
    Hitbox aux = new_duck->get_hitbox();
    aux.move(x, y);
    if (!position_is_valid(aux, true, false)) {
        return false;
    }
    new_duck->move_to(x, y);
    return true;
}

std::vector<duck_DTO> MapGame::get_duck_DTO_list() {
    std::vector<duck_DTO> list_DTO;
    list_DTO.resize(0);
    for (auto it = this->ducks.begin(); it != this->ducks.end(); it++) {
        duck_DTO new_dto = it->second->to_DTO();
        new_dto.is_alive = it->second->is_alive();
        list_DTO.push_back(new_dto);
    }
    for (auto it = this->ducks_dead.begin(); it != this->ducks_dead.end(); it++) {
        duck_DTO new_dto = it->second->to_DTO();
        new_dto.is_alive = it->second->is_alive();
        list_DTO.push_back(new_dto);
    }
    return list_DTO;
}

std::vector<weapon_DTO> MapGame::get_weapons_DTO_list() {
    std::vector<weapon_DTO> list_DTO;
    list_DTO.resize(0);
    for (auto it = this->pickables.begin(); it != this->pickables.end(); it++) {
        weapon_DTO new_dto = (*it)->to_DTO();
        list_DTO.push_back(new_dto);
    }
    for (auto it = this->pickables_spawned.begin(); it != this->pickables_spawned.end(); it++) {
        weapon_DTO new_dto = (*it)->to_DTO();
        list_DTO.push_back(new_dto);
    }
    for (auto it = this->explosives.begin(); it != this->explosives.end(); it++) {
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
    if (!hitbox_in_range(hitbox, false) && not_in_platforms(hitbox, false)) {
        return false;
    }
    this->invalid_positions.insert(hitbox);
    return true;
}

bool MapGame::add_platform(Hitbox hitbox) {
    if (!hitbox_in_range(hitbox, false) && not_in_invalid_position(hitbox, false)) {
        return false;
    }
    this->platforms.insert(hitbox);
    return true;
}

bool MapGame::add_box(Hitbox hitbox) {
    if (!position_is_valid(hitbox, false, false)) {
        return false;
    }
    this->boxes.push_back(std::make_shared<Box>(hitbox.get_x(), hitbox.get_y(), hitbox.get_width(),
                                                hitbox.get_height()));
    return true;
}

bool MapGame::can_move_hitbox(Hitbox hitbox, int dx, int dy, bool can_fall) {
    hitbox.move_relative(dx, dy);
    if (position_is_valid(hitbox, can_fall, false)) {
        return true;
    }
    return false;
}
// bool MapGame::can_move_hitbox_without_boxes(Hitbox hitbox, int dx, int dy) {
//     hitbox.move_relative(dx, dy);
//     if (position_is_valid(hitbox)) {
//         return true;
//     }
//     return false;
// }

bool MapGame::move_relative_if_posible(int duck_id, int dx, int dy) {
    auto duck = this->ducks[duck_id];
    int x_step = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
    int y_step = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;

    int remaining_dx = std::abs(dx);
    int remaining_dy = std::abs(dy);
    
    if(duck_id == 0){
        // Hitbox hitbo = duck->get_hitbox();
        // std::cout << "id: " << duck_id << "x: " << hitbo.get_x() << " y: " << hitbo.get_y() << "height: " << hitbo.get_height() << "width: " << hitbo.get_width() << std::endl;
    }
    if(duck->get_is_sliding()){
        Hitbox aux = duck->get_hitbox();
        aux.move_relative(duck->get_x_direction(), 0);
        if(this->out_of_map(aux)){
            duck->kill();
            this->ducks_dead[duck_id] = duck;
            duck->set_sliding(false);
            return false;
        }
        if (can_move_hitbox(duck->get_hitbox(), duck->get_x_direction(), 0, true) && this->not_in_boxes(aux, false)) {
            duck->move_duck_relative(duck->get_x_direction(), 0);
            duck->set_direction(duck->get_x_direction(), 0);
        } else {
            duck->set_sliding(false);
            return false;
        }
        
        return true;
    }
    while (remaining_dx > 0 || remaining_dy > 0) {
        int step_dx = (remaining_dx > 0) ? x_step : 0;
        int step_dy = (remaining_dy > 0) ? y_step : 0;

        Hitbox aux = duck->get_hitbox();
        aux.move_relative(step_dx, step_dy);
        if(this->out_of_map(aux)){
            duck->kill();
            this->ducks_dead[duck_id] = duck;
            return false;
        }
        if (can_move_hitbox(duck->get_hitbox(), step_dx, step_dy, true) && this->not_in_boxes(aux, false)) {
            duck->move_duck_relative(step_dx, step_dy);
            duck->set_direction(step_dx, step_dy);
        } else {
            return false;
        }

        remaining_dx -= std::abs(step_dx);
        remaining_dy -= std::abs(step_dy);
    }

    return true;
}

void MapGame::respawn_ducks(std::vector<std::tuple<int, int>> positions_to_respawn) {
    int actual_respawn = 0;
    for (auto it = this->ducks_dead.begin(); it != this->ducks_dead.end();) {
        if (it->second->get_respawn_time() == 0) {
            it->second->set_health(HEALTH);
            if(actual_respawn < positions_to_respawn.size()){
                it->second->move_to(std::get<0>(positions_to_respawn[actual_respawn]),
                                std::get<1>(positions_to_respawn[actual_respawn]));
            }else{
                actual_respawn = 0;
                it->second->move_to(std::get<0>(positions_to_respawn[actual_respawn]),
                                std::get<1>(positions_to_respawn[actual_respawn]));
            }
            actual_respawn++;
            this->ducks[it->first] = it->second;
            it = this->ducks_dead.erase(it);
        } else {
            it->second->tick_respawn_time();
            ++it;
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

std::vector<box_DTO> MapGame::get_boxes_DTO() {
    std::vector<box_DTO> vector_boxes(0);
    for (auto& box: this->boxes) {
        box_DTO dto = box->get_DTO();
        vector_boxes.push_back(dto);
    }
    return vector_boxes;
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
    // for(auto explosive = this->explosives.begin(); explosive != this->explosives.end(); ){
    //     (*explosive)->fire_rate_down();
    // }
}

void MapGame::gravity_weapon() {
    for (auto it = pickables.begin(); it != pickables.end(); ++it) {
        //  for(int j=0; j< (count * PRODUCT_FACTOR_GRAVITY) + ADD_FACTOR_GRAVITY; j++){
        (*it)->air_time_down_y();
        Hitbox& hitbox = (*it)->get_reference_hitbox();
        if (!(*it)->is_falling()) {
            this->move_relative_if_posible(hitbox, 0, JUMP_DIRECTION);
            continue;
        }
        if ((*it)->is_falling()) {
            this->move_relative_if_posible(hitbox, 0, GRAVITY);
        }
    }
    for(auto explosive = explosives.begin(); explosive != explosives.end(); ++explosive){
        (*explosive)->air_time_down_y();
        Hitbox& hitbox = (*explosive)->get_reference_hitbox();
        if (!(*explosive)->is_falling()) {
            this->move_relative_if_posible(hitbox, 0, JUMP_DIRECTION);
            continue;
        }
        if ((*explosive)->is_falling()) {
            this->move_relative_if_posible(hitbox, 0, GRAVITY);
        }
    }
}

void MapGame::inertia_weapon() {
    for (auto it = pickables.begin(); it != pickables.end(); ++it) {
        //  for(int j=0; j< (count * PRODUCT_FACTOR_GRAVITY) + ADD_FACTOR_GRAVITY; j++){
        (*it)->air_time_down_x();
        Hitbox& hitbox = (*it)->get_reference_hitbox();
        if ((*it)->is_moving() && (*it)->get_x_direction() > 0) {
            this->move_relative_if_posible(hitbox, RIGHT_DIRECTION, 0);
            continue;
        }
        if ((*it)->is_moving() && (*it)->get_x_direction() < 0) {
            this->move_relative_if_posible(hitbox, LEFT_DIRECTION, 0);
        }
    }
    for (auto explosive = explosives.begin(); explosive != explosives.end(); ++explosive) {
        (*explosive)->air_time_down_x();
        Hitbox& hitbox = (*explosive)->get_reference_hitbox();
        if ((*explosive)->is_moving() && (*explosive)->get_x_direction() > 0) {
            this->move_relative_if_posible(hitbox, RIGHT_DIRECTION, 0);
            continue;
        }
        if ((*explosive)->is_moving() && (*explosive)->get_x_direction() < 0) {
            this->move_relative_if_posible(hitbox, LEFT_DIRECTION, 0);
        }
    }
}

void MapGame::explosives_on_map(){
    for(auto explosive = this->explosives.begin(); explosive != this->explosives.end(); ){
        bool banana_flag = false;
        for (auto it = this->ducks.begin(); it != ducks.end(); ++it) {            
            if (it->second->get_hitbox().has_collision((*explosive)->get_hitbox())) {
                if(!(*explosive)->is_banana()){
                    std::cout << "no es banana" << std::endl;
                    continue;
                }
                std::cout << "deslizando" << std::endl;
                it->second->set_sliding(true);
                explosive = this->explosives.erase(explosive);
                std::cout << "erase banana" << std::endl;
                banana_flag = true;
                break;
            }
        }
        if(banana_flag){ // si no hago esto, va a chequear la banana q ya borre con las cosas d abajo
            continue;
        }
        if((*explosive)->exploted()){
            std::cout << "exploted grenade" << std::endl;
            Hitbox position = (*explosive)->get_hitbox();
            std::vector<std::shared_ptr<BulletInterface>> explotion_bullets = (*explosive)->get_explotion(position);  
            for (int i = 0; i < explotion_bullets.size(); i++) {
                std::cout << "add bullet of explotion" << std::endl;
                this->bullets.push_back(explotion_bullets[i]);
            }
            if(!(*explosive)->is_exploding()){
                explosive = this->explosives.erase(explosive);
                std::cout << "erase grenade" << std::endl;
                continue;
            }
            //break; pq este break? no me permite explotar mas de una granada en el mismo gameloop
            ++explosive;
            continue;    
        }
        (*explosive)->fire_rate_down();
        ++explosive;
    }
}


void MapGame::bullets_next_movement() {
    for (auto bullet = bullets.begin(); bullet != bullets.end();) {
        if ((*bullet)->next_position(*this)) {
            for (auto& [id, duck]: this->ducks) {
                if (!duck->is_alive()) {
                    continue;
                }
                if (duck->get_hitbox().has_collision((*bullet)->get_hitbox())) {
                    int damage = (*bullet)->damage_generated(id);
                    duck->receive_damage(damage);
                    if (!duck->is_alive()) {
                        this->ducks_dead[id] = duck;
                    }
                    break;
                }
            }
            for (auto& box: this->boxes) {
                if (box->get_hitbox().has_collision((*bullet)->get_hitbox())) {
                    int damage = (*bullet)->damage_generated(NOT_OWNER);
                    box->receive_damage(damage);
                    if (box->is_destroyed()) {
                        if (box->get_reward()) {
                            std::shared_ptr<Pickable> item = WeaponFactory::createWeapon(this->get_bullets_list(), "random");
                            item->set_falling(true);
                            item->move_to(box->get_x(), box->get_y());
                            this->pickables.push_back(item);
                        }
                        this->boxes.remove(box);
                        bullet = bullets.erase(bullet);
                        break;
                    }
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

        if (can_move_hitbox(hitbox, step_dx, step_dy, false)) {
            hitbox.move_relative(step_dx, step_dy);
        } else {
            return false;
        }

        remaining_dx -= std::abs(step_dx);
        remaining_dy -= std::abs(step_dy);
    }

    return true;
}

void MapGame::use_item(int duck_id, bool right_direction, bool is_holding, bool looking_up) {
    
    if (!this->duck_exist(duck_id) || !this->duck_is_alive(duck_id)){
        return;
    }
    if(looking_up){
        this->ducks[duck_id]->use_item(NO_DIRECTION, UP_DIRECTION, *this, is_holding);
        return;
    }
    if (right_direction) {
        this->ducks[duck_id]->use_item(RIGHT_DIRECTION, NO_DIRECTION, *this, is_holding);
    } else {
        this->ducks[duck_id]->use_item(LEFT_DIRECTION, NO_DIRECTION, *this, is_holding);
    }

}

// void MapGame::keep_using_item(int duck_id, bool right_direction) {
//     if (!this->duck_exist(duck_id) || !this->duck_is_alive(duck_id)) {
//         return;
//     }
//     if (right_direction) {
//         this->ducks[duck_id]->use_item(RIGHT_DIRECTION, NO_DIRECTION, *this, true);
//     } else {
//         this->ducks[duck_id]->use_item(LEFT_DIRECTION, NO_DIRECTION, *this, true);
//     }
// }

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

bool MapGame::already_exist_a_pickable(int x, int y) {
    for (auto it = this->pickables.begin(); it != this->pickables.end(); ++it) {
        if ((*it)->get_hitbox().has_collision(Hitbox(x, y, 30, 30))) {
            return true;
        }
    }
    for (auto it = this->pickables_spawned.begin(); it != this->pickables_spawned.end(); ++it) {
        if ((*it)->get_hitbox().has_collision(Hitbox(x, y, 30, 30))) {
            return true;
        }
    }

    return false;
}

void MapGame::throw_item(int id_duck, bool right_direction, bool looking_up) {
    std::shared_ptr<Duck> this_duck = this->ducks[id_duck];
    if (this_duck->has_item()) {
        std::shared_ptr<Pickable> weapon = this_duck->throw_item();
        if (weapon == nullptr) {
            return;
        }
        weapon->move_to(this_duck->get_x(), this_duck->get_y());
        if(looking_up){
            weapon->set_direction(NO_DIRECTION, UP_DIRECTION);
            weapon->set_airtime_y(150);
            if(weapon->is_explosive() && weapon->is_active() || weapon->is_banana() && weapon->is_active()){
                this->explosives.push_back(weapon);
                return;
            }
            pickables.push_back(weapon);
            return;
        }else if (right_direction) {
            weapon->set_direction(RIGHT_DIRECTION, JUMP_DIRECTION);
        } else {
            weapon->set_direction(LEFT_DIRECTION, JUMP_DIRECTION);
        }
        if(weapon->is_explosive() && weapon->is_active() || weapon->is_banana() && weapon->is_active()){
            this->explosives.push_back(weapon);
            return;
        }
        pickables.push_back(weapon);
    }
}

void MapGame::ducks_try_throw(int id_duck, bool right_direction) {
    std::shared_ptr<Duck> this_duck = this->ducks[id_duck];
    for (auto it = this->pickables.begin(); it != this->pickables.end();) {
        if (this_duck->get_hitbox().has_collision((*it)->get_hitbox())) {
            std::shared_ptr<Pickable> other_weapon = this_duck->take_item((*it));
            if (other_weapon != nullptr) {
                other_weapon->move_to((*it)->get_x(), (*it)->get_y());
                other_weapon->set_falling(true);
                other_weapon->set_moving(false);
                pickables.push_back(other_weapon);
            }
            it = pickables.erase(it);
            break;
        }
        ++it;
    }
    for (auto it = this->pickables_spawned.begin(); it != this->pickables_spawned.end();) {
        if (this_duck->get_hitbox().has_collision((*it)->get_hitbox())) {
            std::shared_ptr<Pickable> other_weapon = this_duck->take_item((*it));
            if (other_weapon != nullptr) {
                other_weapon->move_to((*it)->get_x(), (*it)->get_y());
                other_weapon->set_falling(true);
                other_weapon->set_moving(false);
                pickables.push_back(other_weapon);
            }
            it = pickables.erase(it);
            break;
        }
        ++it;
    }
}

void MapGame::add_item(std::shared_ptr<Pickable> new_weapon, int x, int y) {
    if(new_weapon == nullptr){
        return;
    }
    if (!this->can_move_hitbox(new_weapon->get_hitbox(), x, y, false)) {
        throw MapError("game can't add item to map");
    }
    new_weapon->move_to(x, y);

    this->pickables_spawned.push_back(new_weapon);
}

std::list<std::shared_ptr<BulletInterface>>& MapGame::get_bullets_list() { return this->bullets; }

void MapGame::clean_map(std::vector<std::tuple<int, int>> positions_to_respawn) {
    int actual_respawn = 0;
    for (auto& [id, duck]: this->ducks) {
        duck->reset();
    }
    for (auto& [id, duck]: this->ducks_dead) {
        duck->reset();
        this->ducks[id] = duck;
        // hay que saber donde tienen que respawnear segun el mapa
    }
    for(auto& [id, duck]: this->ducks){
         if(actual_respawn < positions_to_respawn.size()){
            duck->move_to(std::get<0>(positions_to_respawn[actual_respawn]),
                            std::get<1>(positions_to_respawn[actual_respawn]));
        }else{
            actual_respawn = 0;
            duck->move_to(std::get<0>(positions_to_respawn[actual_respawn]),
                            std::get<1>(positions_to_respawn[actual_respawn]));
        }
        actual_respawn++;
    }
    this->ducks_dead.clear();
    this->bullets.clear();
    this->pickables.clear();
    this->pickables_spawned.clear();
    this->explosives.clear();

    // hay que saber donde tienen que respawnear segun el mapa // falso
}

int MapGame::ducks_dead_size() { return this->ducks_dead.size(); }

bool MapGame::approximate_spawn_to_platform(int x, int& y, int width, int height, bool is_item) {
    while (true) {
        bool collision_found = false;
        for (auto& platform : this->platforms) {
            if (platform.has_collision(Hitbox(x, y, width, height))) {
                collision_found = true;
                break;
            }
        }

        if (!collision_found) {
            y += 1;
        } else {
            y -= 1; 
            break;
        }
        if(y >= this->height){
            y = 0;
            return false;
        }

    }
    if (is_item) {
        y -= 15;
    }else{
        y-= 2;
    }
    return true;
}