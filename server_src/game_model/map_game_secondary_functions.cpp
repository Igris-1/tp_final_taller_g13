#include "map_game.h"

// functions of structures
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

bool MapGame::position_is_valid(Hitbox hitbox, bool can_fall, bool to_stand) {
    if (!hitbox_in_range(hitbox, can_fall)) {
        return false;
    }
    // return not_in_invalid_position(hitbox) && not_in_platforms(hitbox);

    bool uno = not_in_invalid_position(hitbox, to_stand);
    bool dos = not_in_platforms(hitbox, to_stand);
    return uno && dos;
}
bool MapGame::out_of_map(Hitbox hitbox) { return hitbox.get_y() >= this->height; }

bool MapGame::not_in_invalid_position(Hitbox hitbox, bool to_stand) {
    if (!to_stand) {
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
    if (!to_stand) {
        for (Hitbox platform: this->platforms) {
            if (platform.has_collision(hitbox)) {
                return false;
            }
        }
        return true;
    }
    for (Hitbox platform: this->platforms) {
        while (platform.has_collision_above(hitbox)) {
            if (!move_relative_if_posible(hitbox, 0, 1)) {
                return false;
            }
        }
    }
    return true;
}

bool MapGame::not_in_boxes(Hitbox hitbox, bool to_stand) {
    if (!to_stand) {
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

// functions of movements
bool MapGame::can_move_hitbox(Hitbox hitbox, int dx, int dy, bool can_fall) {
    hitbox.move_relative(dx, dy);
    if (position_is_valid(hitbox, can_fall, false)) {
        return true;
    }
    return false;
}

// internal functions
bool MapGame::apply_recoil(std::shared_ptr<Duck> duck, int duck_id) {
    Hitbox aux = duck->get_hitbox();
    aux.move_relative(-(duck->get_x_direction()), 0);
    if (this->out_of_map(aux)) {
        duck->kill();
        this->ducks_dead[duck_id] = duck;
        return false;
    }
    if (can_move_hitbox(duck->get_hitbox(), -1 * (duck->get_x_direction()), 0, true) &&
        this->not_in_boxes(aux, false)) {
        duck->move_duck_relative(-(duck->get_x_direction()), 0);
        duck->set_direction(duck->get_x_direction(), 0);
    } else {
        duck->set_recoil(-1);
        return false;
    }
    return true;
}

bool MapGame::apply_sliding(std::shared_ptr<Duck> duck, int duck_id) {
    Hitbox aux = duck->get_hitbox();
    aux.move_relative(duck->get_x_direction(), 0);
    if (this->out_of_map(aux)) {
        duck->kill();
        this->ducks_dead[duck_id] = duck;
        duck->set_sliding(false);
        return false;
    }
    if (can_move_hitbox(duck->get_hitbox(), duck->get_x_direction(), 0, true) &&
        this->not_in_boxes(aux, false)) {
        duck->move_duck_relative(duck->get_x_direction(), 0);
        duck->set_direction(duck->get_x_direction(), 0);
    } else {
        duck->set_sliding(false);
        return false;
    }
    return true;
}

bool MapGame::apply_movement(std::shared_ptr<Duck> duck, int duck_id, int& remaining_dx,
                             int& remaining_dy, int& x_step, int& y_step) {
    int step_dx = (remaining_dx > 0) ? x_step : 0;
    int step_dy = (remaining_dy > 0) ? y_step : 0;

    Hitbox aux = duck->get_hitbox();
    aux.move_relative(step_dx, step_dy);
    if (this->out_of_map(aux)) {
        duck->kill();
        this->ducks_dead[duck_id] = duck;
        return false;
    }
    if (can_move_hitbox(duck->get_hitbox(), step_dx, step_dy, true) &&
        this->not_in_boxes(aux, false)) {
        duck->move_duck_relative(step_dx, step_dy);
        duck->set_direction(step_dx, step_dy);
    } else {
        return false;
    }

    remaining_dx -= std::abs(step_dx);
    remaining_dy -= std::abs(step_dy);
    return true;
}

void MapGame::explosive_gravity(std::shared_ptr<Pickable> explosive) {
    (explosive)->air_time_down_y();
    Hitbox& hitbox = (explosive)->get_reference_hitbox();
    if (!(explosive)->is_falling()) {
        this->move_relative_if_posible(hitbox, 0, JUMP_DIRECTION);
        return;
    }
    if ((explosive)->is_falling()) {
        this->move_relative_if_posible(hitbox, 0, GRAVITY);
    }
}

void MapGame::inertial_classic_pickable(std::shared_ptr<Pickable> pickable) {
    (pickable)->air_time_down_x();
    Hitbox& hitbox = (pickable)->get_reference_hitbox();
    if ((pickable)->is_moving() && (pickable)->get_x_direction() > 0) {
        this->move_relative_if_posible(hitbox, RIGHT_DIRECTION, 0);
        return;
    }
    if ((pickable)->is_moving() && (pickable)->get_x_direction() < 0) {
        this->move_relative_if_posible(hitbox, LEFT_DIRECTION, 0);
    }
}

void MapGame::inertial_explosive_pickable(std::shared_ptr<Pickable> explosive) {
    (explosive)->air_time_down_x();
    Hitbox& hitbox = (explosive)->get_reference_hitbox();
    if ((explosive)->is_moving() && (explosive)->get_x_direction() > 0) {
        this->move_relative_if_posible(hitbox, RIGHT_DIRECTION, 0);
        return;
    }
    if ((explosive)->is_moving() && (explosive)->get_x_direction() < 0) {
        this->move_relative_if_posible(hitbox, LEFT_DIRECTION, 0);
    }
}

void MapGame::duck_collision_explosive(std::__cxx11::list<std::shared_ptr<Pickable>>::iterator& explosive, bool& banana_flag){
    for (auto it = this->ducks.begin(); it != ducks.end(); ++it) {
        if (it->second->get_hitbox().has_collision((*explosive)->get_hitbox())) {
            if (!(*explosive)->is_banana()) {
                continue;
            }
            this->sounds.duck_sliding = true;
            it->second->set_sliding(true);
            explosive = this->explosives.erase(explosive);
            banana_flag = true;
            break;
        }
    }
}

void MapGame::grenade_exploted(std::__cxx11::list<std::shared_ptr<Pickable>>::iterator& explosive){
    this->sounds.explotion = true;
    Hitbox position = (*explosive)->get_hitbox();
    std::vector<std::shared_ptr<BulletInterface>> explotion_bullets =
            (*explosive)->get_explotion(position);
    for (int i = 0; i < explotion_bullets.size(); i++) {
        this->bullets.push_back(explotion_bullets[i]);
    }
    if (!(*explosive)->is_exploding()) {
        explosive = this->explosives.erase(explosive);
        return;
    }
    ++explosive;
}

bool MapGame::bullet_collision_box(std::shared_ptr<Box>& box, std::__cxx11::list<std::shared_ptr<BulletInterface>>::iterator& bullet, const std::map<std::string, weapon_config>& weapons_config){
    if (box->get_hitbox().has_collision((*bullet)->get_hitbox())) {
        int damage = (*bullet)->damage_generated(NOT_OWNER);
        box->receive_damage(damage);
        if (box->is_destroyed()) {
            if (box->get_reward()) {
                std::shared_ptr<Pickable> item = WeaponFactory::createWeapon(
                        this->get_bullets_list(), "random", weapons_config);
                item->set_falling(true);
                item->move_to(box->get_x(), box->get_y());
                this->pickables.push_back(item);
            }
            this->boxes.remove(box);
            bullet = bullets.erase(bullet);
            return false;
        }
    }
    return true;
}