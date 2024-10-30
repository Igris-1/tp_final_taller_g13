#ifndef PLAYER_COMMANDS_H
#define DUCK_COMMANDS_H

#include "action.h"
#include "../common_src/action_t.h"

class PlayerCommands: public Action{

public:
    action_t action_to_execute;

PlayerCommands(int id, action_t action) 
    : Action(id),
      action_to_execute(action) {
}



void execute(Game& game) override{
    if (action_to_execute.right){
            std::cout << "Moving right" << std::endl;
            Position pos(1,0);
            game.move_duck(this->client_id, pos);
        }
        if (action_to_execute.left){
            std::cout << "Moving left" << std::endl;
            Position pos(-1,0);
            game.move_duck(this->client_id, pos);
        }
    }
};

#endif
