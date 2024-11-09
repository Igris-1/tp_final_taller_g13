#ifndef BULLET_FACTORY_H
#define BULLET_FACTORY_H

#include "bullet_interface.h"
#include "laser.h"
#include "pellet.h"
#include <string>

BulletInterface create_bullets(string bullet_type, int x, int y, int x_direction, int y_direction){
    for(int i=0; i<amount; i++){
        switch(bullet_type){
            case "bullet":
                return Bullet(x, y, x_direction)

        }
    }
    switch (bullet_type)
    {
    case "bullet":
        
        break;
    
    default:
        break;
    }
}

#endif BULLET_FACTORY_H