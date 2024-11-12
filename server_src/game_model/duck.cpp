#include "duck.h"
#include <iostream>

//Duck::Duck(int health) : health(health), armor(0), helmet(0), weapon(0), Positionable(-1,-1), duck_id(0) {}

Duck::Duck(int health, int id) : health(health), armor(nullptr), helmet(nullptr), weapon(std::make_shared<Weapon>(WeaponFactory::createWeapon("laser_rifle"))), Positionable(-1,-1, DUCK_WIDTH, DUCK_HEIGHT), duck_id(id) {}

std::shared_ptr<Weapon> Duck::throw_weapon(){
   if(this->weapon == nullptr){
       return nullptr;
   }
    std::shared_ptr<Weapon> aux = this->weapon;
    this->weapon = nullptr;
    return aux; 
}

int Duck::get_health(){
    return this->health;
}

int Duck::get_id(){
    return this->duck_id;
}

std::shared_ptr<Weapon> Duck::take_weapon(std::shared_ptr<Weapon> weapon){
    std::shared_ptr<Weapon> aux = this->weapon;
    this->weapon = weapon;
    return aux;
}

std::shared_ptr<Armor> Duck::take_armor(std::shared_ptr<Armor> armor){
    std::shared_ptr<Armor> aux = this->armor;
    this->armor = armor;
    return aux;
}

std::shared_ptr<Helmet> Duck::take_helmet(std::shared_ptr<Helmet> helmet){
    std::shared_ptr<Helmet> aux = this->helmet;
    this->helmet = helmet;
    return aux;
}

/*Weapon& Duck::get_weapon(){
    return this->weapon;
}*/

// Armor& Duck::get_armor(){
//     return this->armor;
// }

// Helmet& Duck::get_helmet(){
//     return this->helmet;
// }

bool Duck::is_alive(){
    return !(this->health <= 0);
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

void Duck::continue_fire_rate(){
    this->weapon->fire_rate_down();
}

std::vector<std::shared_ptr<BulletInterface>>  Duck::fire_weapon(int x_direction, int y_direction){
    std::cout << "fire_weapon" << std::endl;
    if(x_direction > 0){
        std::cout << "fire_weapon?" << std::endl;
        return this->weapon->fire(shared_from_this(), this->hitbox.get_x() + (this->hitbox.get_width()), this->hitbox.get_y() + (this->hitbox.get_height())/2, x_direction, y_direction);
    }
    return this->weapon->fire(shared_from_this(), this->hitbox.get_x() , this->hitbox.get_y() + (this->hitbox.get_height())/2, x_direction, y_direction);
}


void Duck::tick_respawn_time(){
    if(this->respawn_time > 0){
        this->respawn_time--;
    }
}

int Duck::get_respawn_time(){
    return this->respawn_time;
}

void Duck::set_health(int health){
    this->health = health;
    this->respawn_time = 100;
}
