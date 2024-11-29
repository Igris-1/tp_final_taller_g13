#include "helmet.h"

#include "../duck.h"

Helmet::Helmet(int width, int height): Pickable(DEFAULT_X, DEFAULT_Y, width, height) {}

void Helmet::use() { this->duck->add_helmet(); }

Helmet::~Helmet() {}

int Helmet::get_id() { return HELMET_ID; }

weapon_DTO Helmet::to_DTO() {
    weapon_DTO dto;
    dto.x = this->hitbox.get_x();
    dto.y = this->hitbox.get_y();
    dto.width = this->hitbox.get_width();
    dto.height = this->hitbox.get_height();
    dto.weapon_id = this->get_id();
    return dto;
}