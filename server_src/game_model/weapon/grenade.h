#ifndef GRENADE_H
#define GRENADE_H

#include "../pickable.h"
#include <vector>
#include "bullets_strategy/bullet_interface.h"
#include "bullets_strategy/bullet.h"
#include "bullets_strategy/laser.h"
#include "bullets_strategy/pellet.h"
#include "weapons_strategy/weapon_interface.h"

class Grenade: public Pickable{
private:
    bool active = false;
    int explosive_time = 2000;
    int explotion_time = 500;

public:
    explicit Grenade(int width, int height);
    void use(MapGame& map);
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
