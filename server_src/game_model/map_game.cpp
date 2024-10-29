#include "map_game.h"

MapGame::MapGame(int high, int width): high(high), width(width) {}

bool MapGame::position_in_range(Position position){
    return (position.get_x() >= 0 && position.get_y() >= 0) && (position.get_x() < this->width && position.get_y() < this->high);
}

bool MapGame::position_is_valid(Position position){
    bool is_valid = this->invalid_positions.find(position) == this->invalid_positions.end();
    return is_valid && position_in_range(position);
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
