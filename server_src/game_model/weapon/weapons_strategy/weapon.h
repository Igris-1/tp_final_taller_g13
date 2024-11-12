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
        int air_time_x = 40;
        int air_time_y = 25;
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
        void keep_moving();
        ~Weapon();

};

#endif // WEAPON_H