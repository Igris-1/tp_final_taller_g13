#include "weapon_interface.h"

bool WeaponInterface::is_real(){
            return true;
        }
        void WeaponInterface::fire_rate_down(){
            if(this->fire_rate > 0){
                this->fire_rate --;
            }
        }