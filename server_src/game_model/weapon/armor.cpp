#include "armor.h"

#include "../duck.h"

Armor::Armor(int width, int height): Pickable(DEFAULT_X, DEFAULT_Y, width, height) {}

void Armor::use() { this->duck->add_armor(); }

int Armor::get_id() { return ARMOR_ID; }

weapon_DTO Armor::to_DTO() {
    weapon_DTO dto;
    dto.x = this->hitbox.get_x();
    dto.y = this->hitbox.get_y();
    dto.width = this->hitbox.get_width();
    dto.height = this->hitbox.get_height();
    dto.weapon_id = this->get_id();
    return dto;
}