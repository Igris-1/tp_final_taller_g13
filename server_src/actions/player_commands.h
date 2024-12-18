#ifndef PLAYER_COMMANDS_H
#define PLAYER_COMMANDS_H

#include "../common_src/action_t.h"

#include "action.h"

class PlayerCommands: public Action {

public:
    action_t action_to_execute;

    PlayerCommands(int id, action_t action): Action(id), action_to_execute(action) {}


    void execute(Game& game) override {
        game.run_duck(this->client_id + action_to_execute.player_id, action_to_execute.left,
                      action_to_execute.right);
        game.stop_run_duck(this->client_id + action_to_execute.player_id,
                           action_to_execute.stop_left, action_to_execute.stop_right);

        game.jump_duck(this->client_id + action_to_execute.player_id, action_to_execute.jump);
        game.stop_jump_duck(this->client_id + action_to_execute.player_id,
                            action_to_execute.stop_jump);

        game.use_duck_item(this->client_id + action_to_execute.player_id,
                           action_to_execute.press_action_button);
        game.stop_duck_item(this->client_id + action_to_execute.player_id,
                            action_to_execute.unpress_action_button);

        game.pick_up_item(this->client_id + action_to_execute.player_id,
                          action_to_execute.press_pick_up_button);

        game.throw_item(this->client_id + action_to_execute.player_id,
                        action_to_execute.press_throw_button);

        game.crouch_duck(this->client_id + action_to_execute.player_id,
                         action_to_execute.press_crouch_button);

        game.stop_crouch_duck(this->client_id + action_to_execute.player_id,
                              action_to_execute.unpress_crouch_button);

        game.duck_looks_up(this->client_id + action_to_execute.player_id,
                           action_to_execute.press_look_up_button);
        game.duck_stops_looking_up(this->client_id + action_to_execute.player_id,
                                   action_to_execute.unpress_look_up_button);

        // game.throw_weapon(this->client_id+action_to_execute.player_id ,
        //  action_to_execute.unpress_pick_up_button);
    }
};

#endif
