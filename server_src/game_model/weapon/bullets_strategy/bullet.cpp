#include "bullet.h"

#include "../../map_game.h"

Bullet::Bullet(int duck_trigger_id, int x, int y, int x_direction, int y_direction, int travel_distance):
        BulletInterface(duck_trigger_id, x, y, x_direction, y_direction) {
            this->travel_distance = travel_distance;
            this->damage = BULLET_DAMAGE;
        }

bool Bullet::next_position(MapGame& map) {
    if (this->travel_distance == 0) {
        return false;
    }
    if (map.move_relative_if_posible(this->hitbox, this->x_direction, this->y_direction)) {
        this->travel_distance--;
        return true;
    }
    return false;
}

int Bullet::get_id() { return BULLET_ID; }