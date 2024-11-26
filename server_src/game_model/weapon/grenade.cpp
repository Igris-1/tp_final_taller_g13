#include "grenade.h"

int Grenade::get_id(){
    return GRENADE_ID;
}

bool Grenade::is_explosive(){
    return true;
}
bool Grenade::is_active(){
    return this->active;   
}

bool Grenade::exploted(){
    return this->explosive_time == 0;
}