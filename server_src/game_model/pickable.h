#ifndef PICKABLE_H
#define PICKABLE_H

#include <memory>

// #include "map_game.h"
#include "../common_src/duck_DTO.h"
#include "positionable.h"

class MapGame;

typedef enum {
    COWBOY_PISTOL_ID = 1,
    LASER_RIFLE_ID,
    AK_47_ID,
    GRENADE_ID,
    MAGNUM_ID,
    OLD_PISTOL_ID,
    PEW_PEW_LASER_ID,
    SHOTGUN_ID,
    SNIPER_ID,
    BANANA_ID,
    HELMET_ID,
    ARMOR_ID,
} ITEM_ID;

class Duck;

class Pickable: public Positionable {

protected:
    // ammo_values[COWBOY_PISTOL_ID] = ParserSingleton::get_instance()->get_value_game("weapon cowboy_pistol shot");
    int air_time_x = 300;
    int air_time_y = 50;

    int x_direction = 0;
    bool moving = true;

    int y_direction = 0;
    bool falling = false;
    std::shared_ptr<Duck> duck;

public:
    Pickable(int x, int y, int width, int height);  // penes de madera
    Pickable();

    virtual void use(MapGame& map) = 0;
    void add_owner(std::shared_ptr<Duck> new_duck);

    // para la caida cool
    virtual int get_id() = 0;
    void air_time_down_y();
    void air_time_down_x();
    bool is_falling();
    bool is_moving();
    void set_falling(bool falling);
    void set_moving(bool moving);
    int get_air_time_y();
    int get_x_direction();
    void set_direction(int x, int y);
    virtual weapon_DTO to_DTO() = 0;

    // metodos vacios
    virtual int recoil_produced();
    virtual void set_holding(bool is_holding);
    virtual void fire_rate_down();
    void set_looking_up(bool looking_up);

    // explosivos
    virtual bool is_explosive();
    virtual bool is_active();
    virtual void activation();
    virtual bool exploted();

    virtual ~Pickable() {}
};

#endif