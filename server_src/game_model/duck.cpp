#include "duck.h"
#include <iostream>
//Duck::Duck(int health) : health(health), armor(0), helmet(0), weapon(0), Positionable(-1,-1), duck_id(0) {}

Duck::Duck(int health, int id) : health(health), armor(0), helmet(0), weapon(WeaponFactory::createWeapon("cowboy")), Positionable(-1,-1, DUCK_WIDTH, DUCK_HEIGHT), duck_id(id) {}

void Duck::throw_weapon_to(Position position){
       //this->weapon.move_to(position);
}

int Duck::get_health(){
    return this->health;
}
int Duck::get_id(){
    return this->duck_id;
}

/*Weapon& Duck::take_weapon(Weapon weapon){
    Weapon& aux = this->weapon;
    this->weapon = weapon;
    //this->weapon.move_to(this->position);
    return aux;
}*/

Armor& Duck::take_armor(Armor armor){
    Armor& aux = this->armor;
    this->armor = armor;
    //this->armor.move_to(this->position);
    return aux;
}

Helmet& Duck::take_helmet(Helmet helmet){
    Helmet& aux = this->helmet;
    this->helmet = helmet;
    //this->helmet.move_to(this->position);
    return aux;
}

/*Weapon& Duck::get_weapon(){
    return this->weapon;
}*/

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

Hitbox Duck::get_hitbox(){
    return this->hitbox;
}

bool Duck::is_this_duck(int id) { return this->duck_id == id; }

duck_DTO Duck::to_DTO(){
    duck_DTO dto;
    dto.duck_id = this->duck_id;
    uint16_t x = this->hitbox.get_x();
    uint16_t y = this->hitbox.get_y();
    dto.x = x;
    dto.y = y;
    dto.width = this->hitbox.get_width();
    dto.height = this->hitbox.get_height();
    //uint8_t duck_hp = this->health;
    //bool weapon_equipped;
    //bool helmet_equipped;
    //bool armor_equipped;
    return dto;
}

std::vector<BulletInterface> Duck::fire_weapon(int x_direction, int y_direction){
    bool is_real;
    return this->weapon.fire(is_real,this->hitbox.get_x() + this->hitbox.get_width(), this->hitbox.get_y() + (this->hitbox.get_height())/2, x_direction, y_direction);
}
