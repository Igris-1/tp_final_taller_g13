#include "laser.h"
#include "../../map_game.h"
#include <ctime>

Laser::Laser(int x, int y, int x_direction, int y_direction) : BulletInterface(x, y, x_direction, y_direction){            
            this->travel_distance = TILES_LASER_DISTANCE;
}
bool Laser::next_position(MapGame& map){
    if(this->travel_distance == 0){
        return false;
    }
    if(map.can_move_hitbox(this->hitbox, this->x_direction, this->y_direction)){
        this->hitbox.move_relative(this->x_direction, this->y_direction);
        this->travel_distance --;
            return true;
    }else{
        this->x_direction *= -1;  
        // this->y_direction += std::rand() % 6;
        this->y_direction *= -1;
        this->hitbox.move_relative(this->x_direction, this->y_direction);
        this->travel_distance--;
        return true;
    }
    return false;
}
