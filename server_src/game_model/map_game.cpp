#include "map_game.h"
#include <iostream>

MapGame::MapGame(int width, int height): height(height), width(width) {}

bool MapGame::position_in_range(Position position){
    return (position.get_x() >= 0 && position.get_y() >= 0) && (position.get_x() < this->width && position.get_y() < this->height);
}

bool MapGame::position_is_valid(Position position){
    if(!position_in_range(position)){
        return false;
    }
    return this->invalid_positions.find(position) == this->invalid_positions.end();
}

bool MapGame::add_invalid_position(Position position){
    if(!position_in_range(position)){
        return false;
    }
    this->invalid_positions.insert(position);
    return true;
}


bool MapGame::move_duck(std::shared_ptr<Duck> duck, Position movement){
   Position aux = duck->get_position() + movement;
        if(position_is_valid(aux)){  
            duck->move_relative_to(movement); 
            return true;
        }
    return false;
}

bool MapGame::set_duck_start_position(std::shared_ptr<Duck> duck, Position position){
    if(!position_is_valid(position)){
        return false;
    }
    duck->move_to(position);
    return true;
}

//void MapGame::print()