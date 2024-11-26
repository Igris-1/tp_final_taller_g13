#ifndef GRENADE_H
#define GRENADE_H

#include "../pickable.h"

class Grenade: public Pickable{
private:
    bool active = false;
    int explosive_time = 2000;

public:
    int get_id() override;
    bool is_explosive() override;
    bool is_active() override;                    
    bool exploted() override;
};

#endif
