#include "bullet.h"
#include "../../map_game.h"

Bullet::Bullet(int duck_trigger_id, int x, int y, int x_direction, int y_direction) : BulletInterface(duck_trigger_id, x, y, x_direction, y_direction){            
            this->travel_distance = TILES_BULLETS;
}

bool Bullet::next_position(MapGame& map){
            if(this->travel_distance == 0){
                return false;
            }
           if(map.can_move_hitbox(this->hitbox, this->x_direction, this->y_direction)){
                this->hitbox.move_relative(this->x_direction, this->y_direction);
                this->travel_distance --;
                return true;
            }
                return false;
}

int Bullet::get_id(){
    return 1;
}