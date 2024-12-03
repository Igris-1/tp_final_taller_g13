#include "i_quit.h"

IQuit::IQuit(int id): Action(id){}


void IQuit::execute(Game& game) {
    game.remove_duck(client_id);
    game.remove_duck(client_id+1); //removes 2nd player if there's one

}


IQuit::~IQuit() {}