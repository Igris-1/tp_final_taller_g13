#include "map_game.h"

MapGame::MapGame(int high, int width): high(high), width(width) {}

bool MapGame::position_in_range(Position position){
    return (position.get_x() >= 0 && position.get_y() >= 0) && (position.get_x() < this->width && position.get_y() < this->high);
}

bool MapGame::position_is_valid(Position position){
    bool is_valid = this->invalid_positions.find(position) == this->invalid_positions.end();
    return is_valid && position_in_range(position);
}

bool MapGame::add_duck(Duck duck){
    Position position = duck.get_position();
    if(!position_is_valid(position)){
        return false;
    }
    this->ducks.push_back(duck);
    return true;
}

bool MapGame::add_invalid_position(Position position){
    if(!position_in_range(position)){
        return false;
    }
    this->invalid_positions.insert(position);
    return true;
}

bool MapGame::move_duck(int duck_id, Position movement){
    for (int i = 0; i < this->ducks.size(); i++){
        if (this->ducks[i].is_this_duck(duck_id)){
            Position aux = this->ducks[i].get_position() + movement;
            if(position_is_valid(aux)){
                this->ducks[i].move_relative_to(movement);
                return true;
            }
            break;
        }
    }
    return false;
}

// bool MapGame::is_this_duck(int id){
    
// }

bool MapGame::add_gun_or_box(Positionable gun_or_box){
    Position position = gun_or_box.get_position();
    if(!position_is_valid(position)){
        return false;
    }
    this->guns_and_boxes.push_back(gun_or_box);
    return true;
}

std::vector<duck_DTO> MapGame::get_duck_DTO_list(){ 
    std::vector<duck_DTO> list_DTO;
    int size_list = this->ducks.size();
    list_DTO.resize(0);
    for(int i=0; i<size_list; i++){
        list_DTO.push_back(this->ducks[i].to_DTO());
    }
    return list_DTO;
}
