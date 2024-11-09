#include "duck_creator.h"
#include "action.h"
#include <iostream>

DuckCreator::DuckCreator(int id)
        : Action(id) {
}


void DuckCreator::execute(Game& game){
    std::cout << "Creating duck for client " << client_id << std::endl;
    game.add_duck(1, this->client_id);
    Position pos = Position(0,0);
    game.set_duck_start_position(this->client_id, pos);
}
