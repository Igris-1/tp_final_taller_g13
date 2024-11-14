#include "weapon_interface.h"

    void WeaponInterface::fire_rate_down(){
        if(this->fire_rate > 0){
            this->fire_rate --;
        }
    }

    bool WeaponInterface::is_explosive(){
        return false;
    }

    bool WeaponInterface::is_active(){
        return false;
    }

    void WeaponInterface::activation(){
        return;
    }

    bool WeaponInterface::exploted(){
        return false;
    }