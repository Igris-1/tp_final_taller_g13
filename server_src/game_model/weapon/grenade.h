#ifndef GRENADE_H
#define GRENADE_H

#include <vector>

#include "../pickable.h"
#include "bullets_strategy/bullet.h"
#include "bullets_strategy/bullet_interface.h"
#include "bullets_strategy/explotion.h"
#include "bullets_strategy/laser.h"
#include "bullets_strategy/pellet.h"
#include "weapons_strategy/weapon_interface.h"

#define EXPLOTION_TIME 100
#define SHRAPNEL_SIZE 32
#define NO_TIME 0

// relatives directions
#define DISPERSION_SMALL 10
#define DISPERSION_MEDIUM 15
#define DISPERSION_BIG 20
#define DISPERSION_HUGE 30

#define HALF 2

class Grenade: public Pickable {
private:
    bool active = false;
    int explotion_time = EXPLOTION_TIME;

    // yaml read
    int damage;
    int scope;
    int reload_time;  // es el tiempo hasta que explota la granada

    std::vector<std::shared_ptr<BulletInterface>> create_explosion(int x, int y);

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
