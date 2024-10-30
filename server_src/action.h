#ifndef ACTION_H
#define ACTION_H

#include "game_model/game.h"

class Action {

protected:
    int client_id;

public:
    virtual void execute(Game& game) = 0;
    virtual ~Action() = default;
};



#endif