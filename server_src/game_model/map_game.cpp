#include "map_game.h"
#include <iostream>

MapGame::MapGame(int width, int height): height(height), width(width) {
}

// bool MapGame::position_in_range(Position position){
//     return (position.get_x() >= 0 && position.get_y() >= 0) && (position.get_x() < this->width && position.get_y() < this->height);
// }

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