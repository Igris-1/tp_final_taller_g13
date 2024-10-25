#include "map_game.h"

MapGame::MapGame(int high, int width): high(high), width(width) {}

bool MapGame::add(Positionable object){
    Position position = object.get_position();
    if(position.get_x() > this->width || position.get_y() > this-> high){
        return false;
    }
    this->positionables.push_back(object);
}

bool MapGame::move_positionable(Positionable item, Position movement){

}
