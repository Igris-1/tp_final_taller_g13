#include "bullet.h"

#include "../../map_game.h"

AKBullet::AKBullet(int duck_trigger_id, int x, int y, int x_direction, int y_direction,
               int travel_distance, int damage, int size, int dispersion):
        BulletInterface(duck_trigger_id, x, y, x_direction, y_direction, damage, size), dispersion(dispersion) {
    this->travel_distance = travel_distance;
}

bool AKBullet::next_position(MapGame& map) {
    if (this->travel_distance == 0) {
        return false;
    }
    // if(this->counter_dispersion == 0){
        if (map.move_relative_if_posible(this->hitbox, this->x_direction, this->y_direction)) {
            this->travel_distance--;
            // this->counter_dispersion = this->dispersion;
            return true;
        }
    // }else{
    //     this->counter_dispersion--;
    //     if (map.move_relative_if_posible(this->hitbox, this->x_direction, this->y_direction)) {
    //         this->travel_distance--;
    //         this->counter_dispersion = this->dispersion;
    //         return true;
    //     }
    // }
    
    return false;
}

int AKBullet::get_id() { return BULLET_ID; }