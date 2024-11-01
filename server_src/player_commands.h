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

        game.run_duck(this->client_id, action_to_execute.left, action_to_execute.right);
        game.stop_run_duck(this->client_id, action_to_execute.stop_left, action_to_execute.stop_right);
        //game.jump_duck(this->client_id, action_to_execute.jump);
    }
};

#endif
