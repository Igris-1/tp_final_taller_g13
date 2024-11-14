#ifndef DUCK_CREATOR_H
#define DUCK_CREATOR_H

#include "action.h"
#include "duck_creator.h"

class DuckCreator: public Action {

public:
    DuckCreator(int id);

    void execute(Game& game) override;

    ~DuckCreator() = default;
};


#endif