#ifndef WEAPON_H
#define WEAPON_H

#include <list>
#include <memory>
#include <vector>

#include "../../pickable.h"
#include "weapon_interface.h"


class Weapon: public Pickable {
protected:
    int dispersion;
    int recoil;
    bool reload_time;
    bool holding_button;

    std::list<std::shared_ptr<BulletInterface>>& bullets;

    std::shared_ptr<WeaponInterface> weapon_strategy;

    bool is_not_a_weapon();

public:
    Weapon(WeaponInterface* weapon_strategy, int width, int height,
           std::list<std::shared_ptr<BulletInterface>>& bullets);


    void fire_rate_down() override;
    weapon_DTO to_DTO();
    int get_id();
    int recoil_produced() override;
    // especiales para la granada y banana
    // void add_owner(std::shared_ptr<Duck> new_duck);
    void set_holding(bool holding) override;
    int get_ammo();
    std::list<std::shared_ptr<BulletInterface>> get_list() { return this->bullets; }
    // -----------------------------------

    void use(MapGame& map) override;
    ~Weapon();
};

#endif  // WEAPON_H