#ifndef PICKABLE_H
#define PICKABLE_H

#include <memory>
#include <vector>

#include "../common_src/DTOs.h"

#include "positionable.h"

#define AIR_TIME_X 300
#define AIR_TIME_Y 50
#define NO_AIRE_TIME 0
#define NO_DIRECTION 0

// defines for bullets
#define NO_OWNER -1
#define RIGHT_DIRECTION 1 
#define LEFT_DIRECTION -1
#define UP_DIRECTION -1
#define DOWN_DIRECTION 1
#define NO_DIRECTION 0

class BulletInterface;

typedef enum {
    NO_WEAPON_ID = 0,
    COWBOY_PISTOL_ID,
    LASER_RIFLE_ID,
    AK_47_ID,
    GRENADE_ID,
    ACTIVATED_GRENADE_ID,
    MAGNUM_ID,
    DUELING_PISTOL_ID,
    PEW_PEW_LASER_ID,
    SHOTGUN_ID,
    SNIPER_ID,
    BANANA_ID,
    OPENED_BANANA_ID,
    HELMET_ID,
    ARMOR_ID,
} ITEM_ID;

class Duck;

class Pickable: public Positionable {

protected:
    int air_time_x = AIR_TIME_X;
    int air_time_y = AIR_TIME_Y;

    int x_direction = NO_DIRECTION;
    bool moving = true;
    
    int y_direction = NO_DIRECTION;
    bool falling = false;
    std::shared_ptr<Duck> duck;

public:
    Pickable(int x, int y, int width, int height);
    Pickable();

    virtual void use() = 0;
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
    virtual int get_sound();
    void set_direction(int x, int y);
    virtual weapon_DTO to_DTO() = 0;
    void set_airtime_y(int airtime);

    // metodos vacios
    virtual int recoil_produced();
    virtual void set_holding(bool is_holding);
    virtual void fire_rate_down();
    void set_looking_up(bool looking_up);

    // explosivos
    virtual bool is_explosive();
    virtual bool is_banana();
    virtual bool is_active();
    virtual void activation();
    virtual bool exploted();
    virtual bool is_exploding();
    virtual std::vector<std::shared_ptr<BulletInterface>> get_explotion(Hitbox hitbox);

    virtual ~Pickable() {}
};

#endif