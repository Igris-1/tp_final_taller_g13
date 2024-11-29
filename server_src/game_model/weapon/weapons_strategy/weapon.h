#ifndef WEAPON_H
#define WEAPON_H

#include <list>
#include <memory>
#include <vector>

#include "../../pickable.h"

#include "weapon_interface.h"

#define HALF 2
#define DIFFERENTIAL_Y -10

#define NO_BULLETS 0
#define NO_WEAPON_SOUND 0


class Weapon: public Pickable {
protected:
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
    void set_holding(bool holding) override;
    int get_ammo();
    std::list<std::shared_ptr<BulletInterface>> get_list() { return this->bullets; }
    // -----------------------------------
    int get_sound() override;
    void use() override;
    ~Weapon();
};

#endif  // WEAPON_H