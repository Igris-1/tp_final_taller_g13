#include "duck_creator.h"
#include "action.h"
#include <iostream>

DuckCreator::DuckCreator(int id)
        : Action(id) {
}


void DuckCreator::execute(Game& game){
    std::cout << "Creating duck for client " << client_id << std::endl;
    game.add_duck(1, this->client_id);
    game.set_duck_start_position(this->client_id, Position(0,0));
    game_snapshot_t gs = game.get_snapshot();
    int x = static_cast<int>(gs.ducks[0].x);
    int y = static_cast<int>(gs.ducks[0].y);
}
