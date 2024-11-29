#ifndef GRENADE_H
#define GRENADE_H

#include "../pickable.h"
#include <vector>
#include "bullets_strategy/bullet_interface.h"
#include "bullets_strategy/bullet.h"
#include "bullets_strategy/laser.h"
#include "bullets_strategy/pellet.h"
#include "bullets_strategy/explotion.h"
#include "weapons_strategy/weapon_interface.h"

class Grenade: public Pickable{
private:
    bool active = false;
    int explotion_time = 100;

     // yaml read
    int damage;
    int scope;
    int reload_time; // es el tiempo hasta que explota la granada

public:
    explicit Grenade(int width, int height, int damage, int scope, int reload_time);
    void use();
    std::vector<std::shared_ptr<BulletInterface>> get_explotion(Hitbox hitbox);
    int get_id() override;
    bool is_explosive() override;
    bool is_exploding() override;
    bool is_active() override;                    
    bool exploted() override;
    void fire_rate_down() override;
    weapon_DTO to_DTO() override;
};

#endif
