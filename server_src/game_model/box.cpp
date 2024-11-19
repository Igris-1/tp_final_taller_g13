#include "box.h"


Box::Box(Hitbox hitbox): Positionable(hitbox), resistance(RESISTANCE){}

void Box::receive_damage(int damage){
    this->resistance -= damage;
    if(this->resistance < 0){
        this->resistance = 0;
    }
}

bool Box::is_destroyed(){
    return this->resistance == 0;
}

bool Box::get_reward(){
    std::srand(std::time(0));
    if(std::rand() % 2){
        return true;
    }
    return false;
}

box_DTO Box::get_DTO(){
    box_DTO box;
    box.x = this->get_x();
    box.y = this->get_y();
    box.width = this->get_width();
    box.height = this->get_height();
    return box;
}