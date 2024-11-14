#include "weapon.h"
#include "../../../../common_src/duck_DTO.h"
#include "../../duck.h"

bool Weapon::is_not_a_weapon(){
            return this->weapon_strategy == nullptr;
        }

Weapon::Weapon(WeaponInterface* weapon_strategy, int width, int height, std::list<std::shared_ptr<BulletInterface>>& bullets):Positionable(0, 0, width, height), 
      weapon_strategy(weapon_strategy), 
      bullets(bullets){}            
      
std::vector<std::shared_ptr<BulletInterface>> Weapon::fire(std::shared_ptr<Duck> duck_trigger, int x_position, int y_position, int& x_direction, int& y_direction){
    if(this->is_not_a_weapon()){
        return std::vector<std::shared_ptr<BulletInterface>>();
    }
    return weapon_strategy->fire(duck_trigger, x_position, y_position, x_direction, y_direction);
}

void Weapon::add_owner(std::shared_ptr<Duck> new_duck){
    this->duck = new_duck;
}

void Weapon::use(){
    if(this->is_not_a_weapon()){
        return;
    }
    std::vector<std::shared_ptr<BulletInterface>> new_bullets = weapon_strategy->fire(
        duck, 
        duck->get_hitbox().get_x() + (duck->get_hitbox().get_width() / 2),
        duck->get_hitbox().get_y() + (duck->get_hitbox().get_height() / 2),
        x_direction, 
        y_direction
    );
    int size = new_bullets.size();
    for(int i = 0; i < size; i++){
        this->bullets.push_back(new_bullets[i]);
    }

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

/* GRANADA Y BANANA VAN A USAR ESTO*/
bool Weapon::is_explosive(){
    if(this->weapon_strategy == nullptr){
        return false;
    }
    return this->weapon_strategy->is_explosive();
}

bool Weapon::is_active(){
    return this->weapon_strategy->is_active();
}
void Weapon::activation(){
    this->weapon_strategy->activation();
}

bool Weapon::exploted(){
    return this->weapon_strategy->exploted();
}
/*--------------------------------------------------------*/

// void Weapon::air_time_down(){
//     if(this->weapon_strategy == nullptr){
//         return;
//     }
//     this->air_time_y--;
//     if(air_time_y == 0){
//         falling = true;
//     }
// }

// bool Weapon::is_falling(){
//     return falling;
// }

// bool Weapon::is_moving(){
//     return moving;
// }

// void Weapon::set_falling(bool falling){
//     this->falling = falling;
// }

// void Weapon::set_moving(bool moving){
//     this->moving = moving;
//     if(moving){
//         this->air_time_x = 300;
//     }
// }

// int Weapon::get_air_time_y(){
//     return this->air_time_y;
// }

// int Weapon::get_x_direction(){
//     return this->x_direction;
// }

// void Weapon::air_time_down_x(){
//     this->air_time_x--;
//     if(air_time_x == 0){
//         // if(this->falling){
//         //     std::cout << "resseteo airtime" << std::endl;
//         //     this->air_time_x = 50;
//         //     return;
//         // }
//         moving = false;
//     }
// }

// void Weapon::set_direction(int x, int y){
//     if(this->weapon_strategy == nullptr){
//         return;
//     }
//     this->x_direction = x;
//     this->y_direction = y;
//     this->air_time_y = 50;
//     this->air_time_x = 300;
// }

Weapon::~Weapon(){
    
}


