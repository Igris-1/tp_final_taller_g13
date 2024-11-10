#ifndef BULLET_INTERFACE_H
#define BULLET_INTERFACE_H

#include "../../position.h"
#include "../../positionable.h"
#include <iostream>
#include "../../common_src/duck_DTO.h"

class MapGame;

class BulletInterface : public Positionable{
    protected:
        int x_direction;
        int y_direction;
        int travel_distance;
        bool bounce_count = false;
        
    public:
        BulletInterface(int x, int y, int x_direction, int y_direction):  Positionable(x, y, 16, 16){
            this->x_direction = x_direction;
            this->y_direction = y_direction;
        }

        int get_x_direction() { return this->x_direction; }

        int get_y_direction() { return this->y_direction; }

        Hitbox get_hitbox(){ return this->hitbox;}

        bullet_DTO to_DTO(){
            bullet_DTO dto;
            dto.x = this->hitbox.get_x();
            dto.y = this->hitbox.get_y();
            dto.width = this->hitbox.get_width();
            dto.height = this->hitbox.get_height();
            dto.x_direction = this->x_direction;
            dto.y_direction = this->y_direction;
            return dto;
        }
        // devuelve true si se puede mover. false si no se puede mover mas
        virtual bool next_position(MapGame& map) = 0;
        //virtual bool can_bounce();
            
        int damage_generated(){
            return 10;
        }
};

#endif

