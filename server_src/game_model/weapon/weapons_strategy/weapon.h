#ifndef WEAPON_H
#define WEAPON_H

#include "positionable.h"
#include "weapon_interface.h"

class Weapon : public Positionable {
    protected:
        int dispersion;
        int recoil;
        bool reload_time;
        WeaponInterface* weapon_strategy; //deberia llamarse weapon_strategy la clase

        bool is_not_a_weapon(){
            return this->weapon_strategy == nullptr;
        }

    public:
        Weapon(int dispersion, int recoil, int reload_time, WeaponInterface* weapon_strategy = nullptr)
            : Positionable(), weapon_strategy(weapon_strategy), dispersion(dispersion), recoil(recoil), reload_time(reload_time) {}
            
        std::vector<std::shared_ptr<BulletInterface>> fire(bool &is_real, int x_position, int y_position, int x_direction, int y_direction){
            if(this->is_not_a_weapon()){
                return std::vector<std::shared_ptr<BulletInterface>>();
            }
            if(this->weapon_strategy->is_real()){
                
                is_real = true;
                return weapon_strategy->fire(x_position, y_position, x_direction, y_direction, dispersion);
            }
            is_real = false;
            return weapon_strategy->fire(x_position, y_position, x_direction, y_direction, dispersion);
        }
        void fire_rate_down(){
            if(this->is_not_a_weapon()) return;
            this->weapon_strategy->fire_rate_down();
        }
        ~Weapon(){
            if(weapon_strategy != nullptr){
                delete this->weapon_strategy;
            }
        }

};

#endif // WEAPON_H