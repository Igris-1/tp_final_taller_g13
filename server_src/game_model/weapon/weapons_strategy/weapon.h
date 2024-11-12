#ifndef WEAPON_H
#define WEAPON_H

#include "positionable.h"
#include "weapon_interface.h"
#include "../../../../common_src/duck_DTO.h"
#include <memory>

class Weapon : public Positionable {
    protected:
        int dispersion;
        int recoil;
        bool reload_time;
        std::shared_ptr<WeaponInterface> weapon_strategy; //deberia llamarse weapon_strategy la clase

        bool is_not_a_weapon();
    public:
        Weapon(int dispersion, int recoil, int reload_time, WeaponInterface* weapon_strategy);
        std::vector<std::shared_ptr<BulletInterface>> fire(int duck_id, int x_position, int y_position, int x_direction, int y_direction);
        void fire_rate_down();
        weapon_DTO to_DTO();
        ~Weapon();

};

#endif // WEAPON_H