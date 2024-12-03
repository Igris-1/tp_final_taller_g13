#ifndef i_QUIT_H
#define i_QUIT_H

#include "action.h"

class IQuit: public Action {

public:
    IQuit(int id);
    void execute(Game& game) override;
    ~IQuit();
};


#endif