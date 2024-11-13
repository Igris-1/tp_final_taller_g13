#ifndef WEAPON_H
#define WEAPON_H

#include "weapon_interface.h"
#include "../../../../common_src/duck_DTO.h"
#include <memory>

class Weapon : public Positionable {
    protected:
        int dispersion;
        int recoil;
        bool reload_time;
        
        int air_time_x = 300;
        int air_time_y = 50;
        
        int x_direction = 0;
        bool moving = true;

        int y_direction = 0;
        bool falling = false;

        std::shared_ptr<WeaponInterface> weapon_strategy; //deberia llamarse weapon_strategy la clase

        bool is_not_a_weapon();
        public:
        Weapon(WeaponInterface* weapon_strategy, int width, int height);

        // devuelvo por x_direction e y_direction el retroceso del pato
        std::vector<std::shared_ptr<BulletInterface>> fire(std::shared_ptr<Duck> duck_trigger, int x_position, int y_position, int& x_direction, int& y_direction);
        void fire_rate_down();
        weapon_DTO to_DTO();
        int get_id();
        int recoil_produced();
        bool is_explosive();
        void air_time_down();
        void air_time_down_x(){
            this->air_time_x--;
            if(air_time_x == 0){
                // if(this->falling){
                //     std::cout << "resseteo airtime" << std::endl;
                //     this->air_time_x = 50;
                //     return;
                // }
                moving = false;
            }
        }
        bool is_falling(){
            return falling;
        }
        bool is_moving(){
            return moving;
        }

        void set_falling(bool falling){
            this->falling = falling;
        }
        void set_moving(bool moving){
            this->moving = moving;
            if(moving){
                this->air_time_x = 300;
            }
        }
        int get_air_time_y(){
            return this->air_time_y;
        }
        int get_x_direction(){
            return this->x_direction;
        }
        void set_direction(int x, int y);
        ~Weapon();

};

#endif // WEAPON_H