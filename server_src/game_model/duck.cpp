#include "duck.h"

Duck::Duck(int health) : health(health), armor(0), helmet(0), weapon(0), Positionable(-1,-1) {}

Position Duck::move_to(Position new_position){
    Position aux = this->position;
    this->position = new_position;
    this->armor.move_to(new_position);
    this->helmet.move_to(new_position);
    this->weapon.move_to(new_position);
    return aux;
}

void Duck::throw_weapon_to(Position position){
    if (this->weapon.is_in_a_live_position()) {
        this->weapon.move_to(position);
    }
}

Weapon& Duck::take_weapon(Weapon weapon){
    Weapon& aux = this->weapon;
    this->weapon = weapon;
    this->weapon.move_to(this->position);
    return aux;
}

Armor& Duck::take_armor(Armor armor){
    Armor& aux = this->armor;
    this->armor = armor;
    this->armor.move_to(this->position);
    return aux;
}

Helmet& Duck::take_helmet(Helmet helmet){
    Helmet& aux = this->helmet;
    this->helmet = helmet;
    this->helmet.move_to(this->position);
    return aux;
}

Weapon& Duck::get_weapon(){
    return this->weapon;
}

Armor& Duck::get_armor(){
    return this->armor;
}

Helmet& Duck::get_helmet(){
    return this->helmet;
}