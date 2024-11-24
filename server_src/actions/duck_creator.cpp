#define NUEVO_MAPA
#include "duck_creator.h"

#include <iostream>

#include "action.h"

DuckCreator::DuckCreator(int id): Action(id) {}


void DuckCreator::execute(Game& game) { game.set_duck_start_position(this->client_id, 0, 0); }
