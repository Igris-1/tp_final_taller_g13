#include "pellet.h"

#include "../../map_game.h"

#define DISPERSION_PELLET 5 

Pellet::Pellet(int duck_trigger_id, int x, int y, int x_direction, int y_direction,
               int travel_distance, int damage, int size, bool vertical):
        BulletInterface(duck_trigger_id, x, y, x_direction, y_direction, damage, size), vertical(vertical) {
    this->travel_distance = travel_distance;
}

bool Pellet::next_position_vertical(MapGame& map){
    if (this->moved_vertical == 0) {
        if (map.move_relative_if_posible(this->hitbox, this->x_direction, this->y_direction)) {
            this->travel_distance--;
            this->moved_vertical = DISPERSION_PELLET;
            return true;
        }
    } else {
        if (map.move_relative_if_posible(this->hitbox, 0, this->y_direction)) {
            this->travel_distance--;
            this->moved_vertical--;
            return true;
        }
    }
    return false;
}

bool Pellet::next_position(MapGame& map) {
    if (this->travel_distance == 0) {
        return false;
    }
    if(this->vertical){
        return next_position_vertical(map);
    }
    if (this->moved_vertical == 0) {
        if (map.move_relative_if_posible(this->hitbox, this->x_direction, this->y_direction)) {
            this->travel_distance--;
            this->moved_vertical = DISPERSION_PELLET;
            return true;
        }
    } else {
        if (map.move_relative_if_posible(this->hitbox, this->x_direction, 0)) {
            this->travel_distance--;
            this->moved_vertical--;
            return true;
        }
    }
    return false;
}

int Pellet::get_id() { return PELLET_ID; }