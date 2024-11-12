#include "weapon.h"
#include "../../../../common_src/duck_DTO.h"
#include "../../duck.h"

bool Weapon::is_not_a_weapon(){
            return this->weapon_strategy == nullptr;
        }

Weapon::Weapon(WeaponInterface* weapon_strategy, int width, int height) : Positionable(0, 0, width, height), weapon_strategy(weapon_strategy){}
            
std::vector<std::shared_ptr<BulletInterface>> Weapon::fire(std::shared_ptr<Duck> duck_trigger, int x_position, int y_position, int& x_direction, int& y_direction){
    if(this->is_not_a_weapon()){
        return std::vector<std::shared_ptr<BulletInterface>>();
    }
    return weapon_strategy->fire(duck_trigger, x_position, y_position, x_direction, y_direction);
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
int Weapon::recoil_produced(){
    return this->weapon_strategy->recoil_produced();
}

int Weapon::get_id(){
    if(this->weapon_strategy == nullptr){
        return 0;
    }
    return this->weapon_strategy->get_id();
}

bool Weapon::is_explosive(){
    if(this->weapon_strategy == nullptr){
        return false;
    }
    return this->weapon_strategy->is_explosive();
}

void Weapon::keep_moving(){
    if(this->weapon_strategy == nullptr){
        return;
    }
    
}

Weapon::~Weapon(){
    
}


