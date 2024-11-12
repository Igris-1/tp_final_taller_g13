#include "weapon.h"
#include "../../../../common_src/duck_DTO.h"

bool Weapon::is_not_a_weapon(){
            return this->weapon_strategy == nullptr;
        }

Weapon::Weapon(int dispersion, int recoil, int reload_time, WeaponInterface* weapon_strategy)
        : Positionable(), weapon_strategy(weapon_strategy), dispersion(dispersion), recoil(recoil), reload_time(reload_time) {}
            
std::vector<std::shared_ptr<BulletInterface>> Weapon::fire(int duck_id, int x_position, int y_position, int x_direction, int y_direction){
    if(this->is_not_a_weapon()){
        return std::vector<std::shared_ptr<BulletInterface>>();
    }
    
    return weapon_strategy->fire(duck_id, x_position, y_position, x_direction, y_direction);
}
void Weapon::fire_rate_down(){
    if(this->is_not_a_weapon()) return;
        this->weapon_strategy->fire_rate_down();
}

weapon_DTO Weapon::to_DTO(){
    if(this->weapon_strategy == nullptr){
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
Weapon::~Weapon(){
    
}


