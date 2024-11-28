#ifndef DUCK_H
#define DUCK_H

#include <memory>
#include <vector>

#include "../../common_src/duck_DTO.h"
#include "weapon/bullets_strategy/bullet_interface.h"
#include "weapon/weapon_factory.h"
#include "positionable.h"


class Pickable;
class Weapon;

#define DUCK_WIDTH 32
#define DUCK_HEIGHT 48
#define DUCK_CROUCH_HEIGHT 36

class Duck: public Positionable, public std::enable_shared_from_this<Duck> {
private:
    // cppcheck-suppress unusedStructMember
    int duck_id;
    int health;
    int begin_health;
    int respawn_time = 100;
    bool has_armor = false;
    bool has_helmet = false;
    int id_weapon;
    int x_direction;
    int y_direction;
    bool is_sliding = false;
    int sliding_counter = 10000;
    std::shared_ptr<Pickable> item_in_hands;

public:

    // DUCK LOGIC
    explicit Duck(int health, int id);
    bool is_alive();
    bool is_this_duck(int id);
    void receive_damage(int damage);
    void kill();
    void set_direction(int step_dx, int step_dy);
    void set_sliding(bool sliding);
    void move_duck_relative(int x, int y);
    ~Duck() {}

    // ITEMS LOGICS
    void use_item(int x_direction, int y_direction, MapGame& map, bool is_holding);
    std::shared_ptr<Pickable> throw_item();
    std::shared_ptr<Pickable> take_item(std::shared_ptr<Pickable> item);
    void add_armor();
    void add_helmet();
    bool has_item();

    void continue_fire_rate();
    bool has_explosive_weapon();
    bool has_active_explosive_weapon();
    void activation_explosive_weapon();
    bool already_exploted();

    // GETTERS
    int get_health();
    int get_id();
    int get_x_direction();
    int get_y_direction();
    Hitbox get_hitbox();
    Hitbox& get_hitbox_reference();
    duck_DTO to_DTO();
    bool get_is_sliding();

    // RESPWAN LOGIC
    void reset();
    void tick_respawn_time();
    int get_respawn_time();
    void set_health(int health);
};

#endif
