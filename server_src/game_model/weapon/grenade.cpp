#include "grenade.h"

Grenade::Grenade(int width, int height, int damage, int scope, int reload_time):
        Pickable(0, 0, width, height), damage(damage), reload_time(reload_time), scope(scope) {}

void Grenade::use() { this->active = true; }

int Grenade::get_id() {
    if (this->active) {
        return ACTIVATED_GRENADE_ID;
    }
    return GRENADE_ID;
}

bool Grenade::is_explosive() { return true; }
bool Grenade::is_active() { return this->active; }

bool Grenade::exploted() { return this->reload_time <= 0; }

weapon_DTO Grenade::to_DTO() {
    weapon_DTO dto;
    dto.x = this->hitbox.get_x();
    dto.y = this->hitbox.get_y();
    dto.width = this->hitbox.get_width();
    dto.height = this->hitbox.get_height();
    dto.weapon_id = this->get_id();
    return dto;
}

std::vector<std::shared_ptr<BulletInterface>> Grenade::create_explosion(int x, int y) {
    std::vector<std::shared_ptr<BulletInterface>> bullets;
    
    const int DX[] = {RIGHT_DIRECTION, NO_DIRECTION, RIGHT_DIRECTION, LEFT_DIRECTION, NO_DIRECTION, LEFT_DIRECTION, RIGHT_DIRECTION};
    const int DY[] = {NO_DIRECTION, DOWN_DIRECTION, DOWN_DIRECTION, NO_DIRECTION, UP_DIRECTION, UP_DIRECTION, UP_DIRECTION};
    const int DISPERSIONS[] = {0, -DISPERSION_SMALL, -DISPERSION_MEDIUM, -DISPERSION_BIG, -DISPERSION_HUGE};

    for (int dir = 0; dir < sizeof(DX) / sizeof(DX[0]); ++dir) { // todas las direcciones
        for (int d = 0; d < sizeof(DISPERSIONS) / sizeof(DISPERSIONS[0]); ++d) { // todas las dispersiones
            bullets.push_back(
                std::make_shared<Explotion>( NO_OWNER, x + DISPERSIONS[d] * DX[dir], 
                    y + DISPERSIONS[d] * DY[dir], DX[dir], DY[dir], TILE_SIZE * this->scope,
                    this->damage, SHRAPNEL_SIZE));
        }
    }
    return bullets;
}

std::vector<std::shared_ptr<BulletInterface>> Grenade::get_explotion(Hitbox hitbox) {
    std::vector<std::shared_ptr<BulletInterface>> bullets;
    int x = hitbox.get_x() + hitbox.get_width() / HALF;
    int y = hitbox.get_y();
    bullets = this->create_explosion(x, y);
    this->explotion_time--;
    return bullets;
}

bool Grenade::is_exploding() { return this->explotion_time > NO_TIME;}

void Grenade::fire_rate_down() {
    if (this->is_active()) {
        this->reload_time--;
    }
}