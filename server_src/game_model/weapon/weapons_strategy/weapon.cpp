#include "weapon.h"

#include "../../../../common_src/duck_DTO.h"
#include "../../duck.h"

bool Weapon::is_not_a_weapon() { return this->weapon_strategy == nullptr; }

Weapon::Weapon(WeaponInterface* weapon_strategy, int width, int height,
               std::list<std::shared_ptr<BulletInterface>>& bullets):
        Pickable(0, 0, width, height), weapon_strategy(weapon_strategy), bullets(bullets) {}

void Weapon::use() {
    if (this->is_not_a_weapon()) {
        return;
    }
    
    std::vector<std::shared_ptr<BulletInterface>> new_bullets = weapon_strategy->fire(
            duck, duck->get_hitbox().get_x() + (duck->get_hitbox().get_width() / 2),
            duck->get_hitbox().get_y() + (duck->get_hitbox().get_height() / 2), x_direction,
            y_direction, this->holding_button);
   int size = new_bullets.size();
    for (int i = 0; i < size; i++) {
        this->bullets.push_back(new_bullets[i]);
    }
}

void Weapon::set_holding(bool holding) {
    if (this->is_not_a_weapon()) {
        return;
    }
    this->holding_button = holding;
}

void Weapon::fire_rate_down() {
    if (this->is_not_a_weapon())
        return;
    this->weapon_strategy->fire_rate_down();
}

weapon_DTO Weapon::to_DTO() {
    if (this->weapon_strategy == nullptr) {
        return weapon_DTO{0, 0, 0, 0, 0};
    }

    weapon_DTO dto;
    dto.x = this->hitbox.get_x();
    dto.y = this->hitbox.get_y();
    dto.width = this->hitbox.get_width();
    dto.height = this->hitbox.get_height();
    dto.weapon_id = this->weapon_strategy->get_id();
    return dto;
}
int Weapon::recoil_produced() {

    return this->weapon_strategy->recoil_produced(); 

}

int Weapon::get_id() {
    if (this->weapon_strategy == nullptr) {
        return 0;
    }
    return this->weapon_strategy->get_id();
}

/* GRANADA Y BANANA VAN A USAR ESTO*/
bool Weapon::is_explosive() {
    if (this->weapon_strategy == nullptr) {
        return false;
    }
    return this->weapon_strategy->is_explosive();
}

bool Weapon::is_active() { return this->weapon_strategy->is_active(); }
void Weapon::activation() { this->weapon_strategy->activation(); }

bool Weapon::exploted() { return this->weapon_strategy->exploted(); }

Weapon::~Weapon() {}
