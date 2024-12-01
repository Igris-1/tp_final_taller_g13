#include "laser.h"

#include "../../map_game.h"

#define CHANGE_DIRECTION -1

Laser::Laser(int duck_trigger_id, int x, int y, int x_direction, int y_direction,
             int travel_distance, int damage, int size):
        BulletInterface(duck_trigger_id, x, y, x_direction, y_direction, damage, size) {
    this->travel_distance = travel_distance;
}
bool Laser::next_position(MapGame& map) {
    if (this->travel_distance == 0) {
        return false;
    }
    if (map.move_relative_if_posible(this->hitbox, this->x_direction, this->y_direction)) {
        this->travel_distance--;
        return true;
    } else {
        this->y_direction *= CHANGE_DIRECTION;
        if (map.move_relative_if_posible(this->hitbox, this->x_direction, this->y_direction)) {
            this->travel_distance--;
            return true;
        }
        this->y_direction *= CHANGE_DIRECTION;
        this->x_direction *= CHANGE_DIRECTION;
        map.move_relative_if_posible(this->hitbox, this->x_direction, this->y_direction);
        this->travel_distance--;
        return true;
    }
}

int Laser::get_id() { return LASER_ID; }