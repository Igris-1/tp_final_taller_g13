#include "map_game.h"

#include <iostream>

MapGame::MapGame(int width, int height, int health): height(height), width(width), HEALTH(health) {
    Hitbox roof (0, 1, width-1, 1);
    this->platforms.insert(roof);
}

int MapGame::get_width() { return this->width; }
int MapGame::get_height() { return this->height; }

bool MapGame::duck_exist(int id) { return this->ducks.find(id) != this->ducks.end(); }

bool MapGame::change_hitbox_size(Hitbox& hitbox, int width, int height, bool to_stand) {
    std::list<Hitbox> hitboxes;
    for (const auto& box : this->boxes) {
        hitboxes.push_back(box->get_hitbox());
    }
    return hitbox.change_size(width, height, this->platforms, hitboxes);
}

bool MapGame::crouch_duck(int id, bool crouch) {
    Hitbox& duck_hitbox = this->ducks[id]->get_hitbox_reference();
    if (!crouch) {}
    if (crouch) {
        return this->change_hitbox_size(duck_hitbox, DUCK_WIDTH, DUCK_CROUCH_HEIGHT, false);
    }
    return this->change_hitbox_size(duck_hitbox, DUCK_WIDTH, DUCK_HEIGHT, true);
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

    if(hitbox.get_y() < 0){
        hitbox.move(hitbox.get_x(), 0);
    }
    if (hitbox.get_y() + hitbox.get_height() > this->height) {
        hitbox.move(hitbox.get_x(), this->height - hitbox.get_height());
    }
    if (hitbox.get_x() < 0) {
        hitbox.move(0, hitbox.get_y());
    }
    if (hitbox.get_x() + hitbox.get_width() > this->width) {
        hitbox.move(this->width - hitbox.get_width(), hitbox.get_y());
    }
    for (const auto& existing_hitbox: this->platforms) {
        if (std::abs(existing_hitbox.get_y() - hitbox.get_y()) <= PLATFORM_MAXIMUM_DISTANCE) {
            hitbox.move(hitbox.get_x() ,existing_hitbox.get_y());
            break; 
        }
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

bool MapGame::move_relative_if_posible(int duck_id, int dx, int dy) {
    auto duck = this->ducks[duck_id];
    int x_step = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
    int y_step = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;

    int remaining_dx = std::abs(dx);
    int remaining_dy = std::abs(dy);

    if (duck->has_recoil()) {
        if (!this->apply_recoil(duck, duck_id))
            return false;
    }
    if (duck->get_is_sliding()) {
        return this->apply_sliding(duck, duck_id);
    }
    while (remaining_dx > 0 || remaining_dy > 0) {
        if (!this->apply_movement(duck, duck_id, remaining_dx, remaining_dy, x_step, y_step)) {
            return false;
        }
    }

    return true;
}

void MapGame::respawn_ducks(std::vector<std::tuple<int, int>> positions_to_respawn) {
    int actual_respawn = 0;
    for (auto it = this->ducks_dead.begin(); it != this->ducks_dead.end();) {
        if (it->second->get_respawn_time() == 0) {
            it->second->set_health(HEALTH);
            if (actual_respawn < positions_to_respawn.size()) {
                it->second->move_to(std::get<X_POSITION>(positions_to_respawn[actual_respawn]),
                                    std::get<Y_POSITION>(positions_to_respawn[actual_respawn]));
            } else {
                actual_respawn = 0;
                it->second->move_to(std::get<X_POSITION>(positions_to_respawn[actual_respawn]),
                                    std::get<Y_POSITION>(positions_to_respawn[actual_respawn]));
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

void MapGame::continue_fire_rate(int id, int speed_of_game) {
    int check;
    if (this->duck_exist(id)) {
        check = this->ducks[id]->continue_fire_rate(speed_of_game);
    }
    if(check == GRENADE_EXPLOTED_ON_HAND){
        this->throw_item(id, true, true);
    }
}

void MapGame::gravity_weapon() {
    for (auto it = pickables.begin(); it != pickables.end(); ++it) {
        (*it)->air_time_down_y();
        Hitbox& hitbox = (*it)->get_reference_hitbox();
        if (!(*it)->is_falling()) {
            this->move_relative_if_posible(hitbox, NO_DIRECTION, JUMP_DIRECTION);
            continue;
        }
        if ((*it)->is_falling()) {
            this->move_relative_if_posible(hitbox, NO_DIRECTION, GRAVITY);
        }
    }
    for (auto explosive = explosives.begin(); explosive != explosives.end(); ++explosive) {
        this->explosive_gravity(*explosive);
    }
}

void MapGame::inertia_weapon() {
    for (auto it = pickables.begin(); it != pickables.end(); ++it) {
        this->inertial_classic_pickable(*it);
    }
    for (auto explosive = explosives.begin(); explosive != explosives.end(); ++explosive) {
        this->inertial_explosive_pickable(*explosive);
    }
}

void MapGame::explosives_on_map() {
    for (auto explosive = this->explosives.begin(); explosive != this->explosives.end();) {
        bool banana_flag = false;
        this->duck_collision_explosive(explosive, banana_flag);
        if (banana_flag) {  // si no hago esto, va a chequear la banana q ya borre con las cosas de abajo                // abajo
            continue;
        }
        if ((*explosive)->exploted()) {
            this->grenade_exploted(explosive);
            continue;
        }
        (*explosive)->fire_rate_down();
        ++explosive;
    }
}

void MapGame::bullets_next_movement(const std::map<std::string, weapon_config>& weapons_config) {
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
                if(!bullet_collision_box(box, bullet, weapons_config)){
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
    int sound;
    if (!this->duck_exist(duck_id) || !this->duck_is_alive(duck_id)) {
        return;
    }
    if (looking_up) {
        sound = this->ducks[duck_id]->use_item(NO_DIRECTION, UP_DIRECTION, is_holding);
        set_bullet_sound(sound);
        return;
    }
    if (right_direction) {
        sound = this->ducks[duck_id]->use_item(RIGHT_DIRECTION, NO_DIRECTION, is_holding);
    } else {
        sound = this->ducks[duck_id]->use_item(LEFT_DIRECTION, NO_DIRECTION, is_holding);
    }
    set_bullet_sound(sound);
}

void MapGame::set_bullet_sound(int sound) {
    this->sounds.shooting_small_weapon = (sound == SHOOTING_SMALL_WEAPON) ? true : false;
    this->sounds.shooting_big_weapon = (sound == SHOOTING_BIG_WEAPON) ? true : false;
    this->sounds.shooting_laser_weapon = (sound == SHOOTING_LASER_WEAPON) ? true : false;
}

bool MapGame::already_exist_a_pickable(int x, int y, int width, int height) {
    for (auto it = this->pickables_spawned.begin(); it != this->pickables_spawned.end(); ++it) {
        if ((*it)->get_hitbox().has_collision(Hitbox(x, y, width, height))) {
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
        if (looking_up) {
            weapon->set_direction(NO_DIRECTION, UP_DIRECTION);
            weapon->set_airtime_y(AIR_TIME_Y_THROW);
            if (weapon->is_explosive() && weapon->is_active() ||
                weapon->is_banana() && weapon->is_active()) {
                this->explosives.push_back(weapon);
                return;
            }
            pickables.push_back(weapon);
            return;
        } else if (right_direction) {
            weapon->set_direction(RIGHT_DIRECTION, JUMP_DIRECTION);
        } else {
            weapon->set_direction(LEFT_DIRECTION, JUMP_DIRECTION);
        }
        if (weapon->is_explosive() && weapon->is_active() ||
            weapon->is_banana() && weapon->is_active()) {
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
    if (new_weapon == nullptr) {
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
    }
    for (auto& [id, duck]: this->ducks) {
        if (actual_respawn < positions_to_respawn.size()) {
            duck->move_to(std::get<X_POSITION>(positions_to_respawn[actual_respawn]),
                          std::get<Y_POSITION>(positions_to_respawn[actual_respawn]));
        } else {
            actual_respawn = 0;
            duck->move_to(std::get<X_POSITION>(positions_to_respawn[actual_respawn]),
                          std::get<Y_POSITION>(positions_to_respawn[actual_respawn]));
        }
        actual_respawn++;
    }
    this->ducks_dead.clear();
    this->bullets.clear();
    this->pickables.clear();
    this->pickables_spawned.clear();
    this->explosives.clear();
}

int MapGame::ducks_dead_size() { return this->ducks_dead.size(); }

bool MapGame::approximate_spawn_to_platform(Hitbox& hitbox, bool is_item) {
    while (true) {
        bool collision_found = false;
        for (auto& platform: this->platforms) {
            if (platform.has_collision(hitbox)) {
                collision_found = true;
                break;
            }
        }

        if (!collision_found) {
            hitbox.move_relative(NO_DIRECTION, GRAVITY);
        } else {
            hitbox.move_relative(NO_DIRECTION, JUMP_DIRECTION);
            break;
        }
        if (hitbox.get_y() >= this->height) {
            hitbox.move(hitbox.get_x(), 0); // si se va de rango, lo mando al principio del mapa
            return false;
        }
    }
    if (is_item) {
        hitbox.move_relative(NO_DIRECTION, PICKABLE_SPAWN_DISTANCE_TO_PLATFORM);
    } else {
        hitbox.move_relative(NO_DIRECTION, DUCK_SPAWN_DISTANCE_TO_PLATFORM);
    }
    return true;
}

sounds_DTO MapGame::get_sounds_DTO() {
    sounds_DTO dto = this->sounds;
    this->sounds = sounds_DTO();
    return dto;
}