#include "laser.h"

#include "../../map_game.h"

Laser::Laser(int duck_trigger_id, int x, int y, int x_direction, int y_direction):
        BulletInterface(duck_trigger_id, x, y, x_direction, y_direction) {
    this->travel_distance = TILES_LASER_DISTANCE;
    this->damage = 50;
}
bool Laser::next_position(MapGame& map) {
    if (this->travel_distance == 0) {
        return false;
    }
    if (map.move_relative_if_posible(this->hitbox, this->x_direction, this->y_direction)) {
        this->travel_distance--;
        return true;
    } else {
        this->y_direction *= -1;
        if(map.move_relative_if_posible(this->hitbox, this->x_direction, this->y_direction)){
            this->travel_distance--;
            return true;
        }
        this->y_direction *= -1;
        this->x_direction *= -1;
        map.move_relative_if_posible(this->hitbox, this->x_direction, this->y_direction);
        this->travel_distance--;
        return true;
    }
}

int Laser::get_id() { return 2; }