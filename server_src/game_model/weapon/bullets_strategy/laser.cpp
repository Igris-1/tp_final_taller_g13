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
#ifndef NUEVO_MAPA
    if (map.can_move_hitbox(this->hitbox, this->x_direction, this->y_direction)) {
        this->hitbox.move_relative(this->x_direction, y_direction);
        this->travel_distance--;
        return true;
    } else {
        // this->x_direction *= -1;
        // this->y_direction += std::rand() % 6;
        this->y_direction *= -1;
        this->hitbox.move_relative(this->x_direction, y_direction);
        this->travel_distance--;
        return true;
    }
#endif  // lo dejo asi pq no se como usarlo todavia

#ifdef NUEVO_MAPA

    if (map.move_relative_if_posible(this->hitbox, this->x_direction, this->y_direction)) {
        this->travel_distance--;
        return true;
    } else {
        this->y_direction *= -1;
        map.move_relative_if_posible(this->hitbox, this->x_direction, this->y_direction);
        this->travel_distance--;
        return true;
    }

#endif
}

int Laser::get_id() { return 2; }