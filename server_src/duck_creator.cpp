#include "duck_creator.h"
#include "action.h"

DuckCreator::DuckCreator(int id){
    this->client_id = id;
}

void DuckCreator::execute(Game& game){
    std::cout << "Creating duck for client " << client_id << std::endl;
    game.add_duck(1, this->client_id);
}