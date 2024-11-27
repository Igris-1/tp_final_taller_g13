#include "banana.h"

Banana::Banana(int width, int height) : Pickable(0, 0, width, height){

}

void Banana::use(MapGame& map){
    this->active = true;
}

int Banana::get_id(){
    if(this->active){
        return OPENED_BANANA_ID;
    }
    return BANANA_ID;
}

bool Banana::is_active(){
    return this->active;   
}

bool Banana::is_explosive(){
    return true;
}

weapon_DTO Banana::to_DTO(){
    weapon_DTO dto;
    dto.x = this->hitbox.get_x();
    dto.y = this->hitbox.get_y();
    dto.width = this->hitbox.get_width();
    dto.height = this->hitbox.get_height();
    dto.weapon_id = this->get_id();
    return dto;
}
Banana::~Banana(){}