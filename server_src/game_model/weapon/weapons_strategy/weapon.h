#ifndef WEAPON_H
#define WEAPON_H

#include "positionable.h"
#include "weapon_interface.h"

class Weapon : public Positionable {
    protected:
        int dispersion;
        int recoil;
        bool reload_time;
        WeaponInterface* weapon_strategy;

    public:
        Weapon(int dispersion, int recoil, int reload_time, WeaponInterface* weapon_strategy_si)
            : Positionable(), weapon_strategy(weapon_strategy_si), dispersion(dispersion), recoil(recoil), reload_time(reload_time) {}
            
        std::vector<BulletInterface> fire(bool &is_real, int x_position, int y_position, int x_direction, int y_direction){
            if(this->weapon_strategy->is_real()){
                
                is_real = true;
                return weapon_strategy->fire(x_position, y_position, x_direction, y_direction, dispersion);
            }
            is_real = false;
            return weapon_strategy->fire(x_position, y_position, x_direction, y_direction, dispersion);
        }

};

#endif // WEAPON_H