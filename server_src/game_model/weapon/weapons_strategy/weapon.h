#ifndef WEAPON_H
#define WEAPON_H

#include <list>
#include <memory>
#include <vector>

#include "../../../../common_src/duck_DTO.h"
#include "../../pickable.h"

#include "weapon_interface.h"

class Weapon: public Positionable, public Pickable {
protected:
    int dispersion;
    int recoil;
    bool reload_time;

    std::shared_ptr<Duck> duck;

    std::list<std::shared_ptr<BulletInterface>>& bullets;

    // int air_time_x = 300;
    // int air_time_y = 50;

    // int x_direction = 0;
    // bool moving = true;

    // int y_direction = 0;
    // bool falling = false;

    std::shared_ptr<WeaponInterface> weapon_strategy;  // deberia llamarse weapon_strategy la clase

    bool is_not_a_weapon();

public:
    Weapon(WeaponInterface* weapon_strategy, int width, int height,
           std::list<std::shared_ptr<BulletInterface>>& bullets);

    // devuelvo por x_direction e y_direction el retroceso del pato
    std::vector<std::shared_ptr<BulletInterface>> fire(std::shared_ptr<Duck> duck_trigger,
                                                       int x_position, int y_position,
                                                       int& x_direction, int& y_direction);
    void fire_rate_down();
    weapon_DTO to_DTO();
    int get_id();
    int recoil_produced();
    // especiales para la granada y banana
    void add_owner(std::shared_ptr<Duck> new_duck);
    bool is_explosive();
    bool is_active();
    void activation();
    bool exploted();
    std::list<std::shared_ptr<BulletInterface>> get_list() { return this->bullets; }
    // -----------------------------------

    void use();
    ~Weapon();
};

#endif  // WEAPON_H