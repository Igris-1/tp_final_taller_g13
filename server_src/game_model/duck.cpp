#include "duck.h"

//Duck::Duck(int health) : health(health), armor(0), helmet(0), weapon(0), Positionable(-1,-1), duck_id(0) {}

Duck::Duck(int health, int id) : health(health), armor(0), helmet(0), weapon(0), Positionable(-1,-1), duck_id(id) {}

//comento para q compile
void Duck::throw_weapon_to(Position position){
       this->weapon.move_to(position);
}

int Duck::get_health(){
    return this->health;
}
int Duck::get_id(){
    return this->duck_id;
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

bool Duck::is_alive(){
    return !(this->health == 0);
}

void Duck::receive_damage(int damage){
    this->health -= damage;
    if (this->health < 0){
        this->health = 0;
    }
}

bool Duck::is_this_duck(int id) { return this->duck_id == id; }

duck_DTO Duck::to_DTO(){
    duck_DTO dto;
    dto.duck_id = this->duck_id;
    uint16_t x = this->position.get_x();
    uint16_t y = this->position.get_y();
    dto.x = x;
    dto.y = y;
    //uint8_t duck_hp = this->health;
    //bool weapon_equipped;
    //bool helmet_equipped;
    //bool armor_equipped;
    return dto;
}