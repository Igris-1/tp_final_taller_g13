#include "bullet_interface.h"


BulletInterface::BulletInterface(int duck_trigger_id, int x, int y, int x_direction,
                                 int y_direction, int damage, int size):
        Positionable(x, y, size, size/2), duck_trigger_id(duck_trigger_id), damage(damage) {
    this->x_direction = x_direction;
    this->y_direction = y_direction;
}

int BulletInterface::get_x_direction() { return this->x_direction; }

int BulletInterface::get_y_direction() { return this->y_direction; }

Hitbox BulletInterface::get_hitbox() { return this->hitbox; }

bullet_DTO BulletInterface::to_DTO() {
    bullet_DTO dto;
    dto.x = this->hitbox.get_x();
    dto.y = this->hitbox.get_y();
    dto.width = this->hitbox.get_width();
    dto.height = this->hitbox.get_height();
    dto.x_direction = this->x_direction;
    dto.y_direction = this->y_direction;
    dto.bullet_id = static_cast<uint8_t>(this->get_id());
    return dto;
}

int BulletInterface::damage_generated(int duck_id) {
    if (this->duck_trigger_id == duck_id) {
        return 0;
    }
    this->travel_distance = 0;
    return this->damage;
}