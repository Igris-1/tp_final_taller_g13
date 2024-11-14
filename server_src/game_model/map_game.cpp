#include "map_game.h"
#include <iostream>


#ifndef NUEVO_MAPA
MapGame::MapGame(int width, int height): height(height), width(width){
}

    bool MapGame::hitbox_in_range(Hitbox hitbox) {
    int hitbox_left = hitbox.get_x();
    int hitbox_right = hitbox.get_x() + hitbox.get_width();
    int hitbox_top = hitbox.get_y();
    int hitbox_bottom = hitbox.get_y() + hitbox.get_height();

    return (hitbox_left >= 0 && hitbox_right <= this->width &&
            hitbox_top >= 0 && hitbox_bottom <= this->height);
}

bool MapGame::not_in_invalid_position(Hitbox hitbox){
    for(Hitbox invalid_position: this->invalid_positions){
        if(invalid_position.has_collision(hitbox)){
            return false;
        }
    }
    return true;
}

bool MapGame::not_in_platforms(Hitbox hitbox){
    for(Hitbox platform: this->platforms){
        if(platform.has_collision(hitbox)){
            return false;
        }
    }
    return true;
}

bool MapGame::position_is_valid(Hitbox hitbox){
    if(!hitbox_in_range(hitbox)){
        return false;
    }
    return not_in_invalid_position(hitbox) && not_in_platforms(hitbox);
}

bool MapGame::add_invalid_position(Hitbox hitbox){
    if(!hitbox_in_range(hitbox) && not_in_platforms(hitbox)){
        return false;
    }
    this->invalid_positions.insert(hitbox);
    return true;
}

bool MapGame::add_platform(Hitbox hitbox){
    if(!hitbox_in_range(hitbox) && not_in_invalid_position(hitbox)){
        //std::cout << "hubo un false" << std::endl;
        return false;
    }
    this->platforms.insert(hitbox);
    return true;
}


bool MapGame::move_duck(std::shared_ptr<Duck> duck, int dx, int dy){
    Hitbox aux = duck->get_hitbox();
    aux.move_relative(dx, dy);
        if(position_is_valid(aux)){  
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

bool MapGame::can_move_hitbox(Hitbox hitbox, int dx, int dy){
    hitbox.move_relative(dx, dy);
        if(position_is_valid(hitbox)){  
            return true;
        }
    return false;
}

bool MapGame::set_duck_start_position(std::shared_ptr<Duck> duck, int x, int y){
    Hitbox aux = duck->get_hitbox();
    aux.move(x, y);
    if(!position_is_valid(aux)){
        return false;
    }
    duck->move_to(x, y);
    return true;
}


std::vector<platform_DTO> MapGame::get_platforms_DTO(){
    std::vector<platform_DTO> vector_platforms;
    vector_platforms.resize(0);
    for(Hitbox p: this->platforms){
        platform_DTO dto = {static_cast<uint16_t>(p.get_x()), static_cast<uint16_t>(p.get_y()), static_cast<uint16_t>(p.get_width()), static_cast<uint16_t>(p.get_height())};
        vector_platforms.push_back(dto);
    }
    return vector_platforms;
}


#endif

/*------NUEVOOOOOOOOOOOO -----------------------------------------------------------------
-------------------------MAPAAAAAAAA ---------------------------------------------------*/

#ifdef NUEVO_MAPA

MapGame::MapGame(int width, int height): height(height), width(width){}

bool MapGame::duck_exist(int id){
    return this->ducks.find(id) != this->ducks.end();

}

bool MapGame::not_in_invalid_position(Hitbox hitbox){
    for(Hitbox invalid_position: this->invalid_positions){
        if(invalid_position.has_collision(hitbox)){
            return false;
        }
    }
    return true;
}

bool MapGame::not_in_platforms(Hitbox hitbox){
    for(Hitbox platform: this->platforms){
        if(platform.has_collision(hitbox)){
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

    return (hitbox_left >= 0 && hitbox_right <= this->width &&
            hitbox_top >= 0 && hitbox_bottom <= this->height);
}

bool MapGame::position_is_valid(Hitbox hitbox){
    if(!hitbox_in_range(hitbox)){
        return false;
    }
    return not_in_invalid_position(hitbox) && not_in_platforms(hitbox);
}

bool MapGame::set_duck_start_position(std::shared_ptr<Duck> duck, int x, int y){
    Hitbox aux = duck->get_hitbox();
    aux.move(x, y);
    if(!position_is_valid(aux)){
        return false;
    }
    duck->move_to(x, y);
    this->ducks[duck->get_id()] = duck;
    return true;
}

std::vector<duck_DTO> MapGame::get_duck_DTO_list(){
    std::vector<duck_DTO> list_DTO;
    for(auto it = this->ducks.begin(); it != this->ducks.end(); it++){
        duck_DTO new_dto = it->second->to_DTO();
        new_dto.is_alive = it->second->is_alive();
        list_DTO.push_back(new_dto);
    }
    return list_DTO;
}

bool MapGame::duck_is_alive(int id){
    if(this->ducks.find(id) == this->ducks.end()){
        throw MapError("El pato no existe");
    }
    return this->ducks[id]->is_alive();
}

bool MapGame::add_invalid_position(Hitbox hitbox){
    if(!hitbox_in_range(hitbox) && not_in_platforms(hitbox)){
        return false;
    }
    this->invalid_positions.insert(hitbox);
    return true;
}

bool MapGame::add_platform(Hitbox hitbox){
    if(!hitbox_in_range(hitbox) && not_in_invalid_position(hitbox)){
        //std::cout << "hubo un false" << std::endl;
        return false;
    }
    this->platforms.insert(hitbox);
    return true;
}

bool MapGame::can_move_hitbox(Hitbox hitbox, int dx, int dy){
    hitbox.move_relative(dx, dy);
        if(position_is_valid(hitbox)){  
            return true;
        }
    return false;
}

bool MapGame::move_relative_if_posible(int id, int dx, int dy){
    auto duck = this->ducks[id];
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

void MapGame::respawn_ducks(){
    for(auto it = this->ducks.begin(); it != this->ducks.end(); it++){
        if(!it->second->is_alive() && it->second->get_respawn_time() == 0){
            it->second->set_health(100);
        }
        else if(!it->second->is_alive()){
            it->second->tick_respawn_time();
        }
     }
}

std::vector<int> MapGame::get_live_duck_ids(){
    std::vector<int> live_duck_ids;
    for(auto it = this->ducks.begin(); it != this->ducks.end(); it++){
        if(it->second->is_alive()){
            live_duck_ids.push_back(it->first);
        }
    }
    return live_duck_ids;
}

std::vector<int> MapGame::get_all_duck_ids(){
    std::vector<int> duck_ids;
    for(auto it = this->ducks.begin(); it != this->ducks.end(); it++){
            duck_ids.push_back(it->first);
    }
    return duck_ids;
}

void MapGame::remove_duck(int id){
    if(this->ducks.find(id) == this->ducks.end()){
        return;
    }
    this->ducks.erase(id);
}

std::vector<platform_DTO> MapGame::get_platforms_DTO(){
    std::vector<platform_DTO> vector_platforms;
    vector_platforms.resize(0);
    for(Hitbox p: this->platforms){
        platform_DTO dto = {static_cast<uint16_t>(p.get_x()), static_cast<uint16_t>(p.get_y()), static_cast<uint16_t>(p.get_width()), static_cast<uint16_t>(p.get_height())};
        vector_platforms.push_back(dto);
    }
    return vector_platforms;
}

#endif