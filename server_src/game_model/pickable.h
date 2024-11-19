#ifndef PICKABLE_H
#define PICKABLE_H

#include <memory>

typedef enum {
    COWBOY_PISTOL_ID = 1,
    LASER_RIFLE_ID,
    GRENADE_ID,
    HELMET_ID,
    ARMOR_ID,
} ITEM_ID;

class Duck;

class Pickable /*: public Positionable */ {

protected:
    int air_time_x = 300;
    int air_time_y = 50;

    int x_direction = 0;
    bool moving = true;

    int y_direction = 0;
    bool falling = false;

    std::shared_ptr<Duck> duck;    
   // std::shared_ptr<Hitbox> hitbox;

public:
    virtual void use() = 0;
    void add_owner(std::shared_ptr<Duck> new_duck);
   // void add_owner2(std::shared_ptr<Hitbox> new_hitbox);

    // para la caida cool
    void air_time_down_y();
    void air_time_down_x();
    bool is_falling();
    bool is_moving();
    void set_falling(bool falling);
    void set_moving(bool moving);
    int get_air_time_y();
    int get_x_direction();
    void set_direction(int x, int y);

    ~Pickable() = default;
};


#endif