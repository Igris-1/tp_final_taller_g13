#ifndef BULLET_INTERFACE_H
#define BULLET_INTERFACE_H

#include "../../position.h"
#include "../../positionable.h"
#include <iostream>

class BulletInterface : public Positionable{
    protected:
        int x_direction;
        int y_direction;
        int tiles_acount;
    public:
        BulletInterface(int x, int y, int x_direction, int y_direction):  Positionable(x, y, 8, 8){
            this->x_direction = x_direction;
            this->y_direction = y_direction;
            this->tiles_acount =1000;
        }
        //virtual void next_position(int &x, int &y);
        int get_x_direction() { return this->x_direction; }
        int get_y_direction() { return this->y_direction; }
        Hitbox get_hitbox(){ return this->hitbox;}
        void print_position(){ std::cout << "bala en posicion x: " << this->hitbox.get_x() << " y: " << this->hitbox.get_y() << std::endl;}
        
        bool is_dead() { return this->tiles_acount == 0; }
};

#endif

