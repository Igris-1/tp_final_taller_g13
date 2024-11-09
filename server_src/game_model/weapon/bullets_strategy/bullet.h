#ifndef BULLET_H
#define BULLET_H

#include "bullet_interface.h"

#define TILES_BULLETS

class Bullet : public BulletInterface{
    private:

    public:
        Bullet(int x, int y, int x_direction, int y_direction) : BulletInterface(x, y, x_direction, y_direction){            
        }
        // void next_position(int &x, int &y){
               
        // }A
};

#endif
