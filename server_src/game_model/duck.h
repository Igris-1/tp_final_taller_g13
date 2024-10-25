#pragma once

#include "armor.h"
#include "helmet.h"
#include "positionable.h"
#include "weapon.h"

class Duck: public Positionable {
private:
    // cppcheck-suppress unusedStructMember
    int duck_id;
    int health;
    Armor armor;
    Helmet helmet;
    Weapon weapon; 

public:
    // por defecto empieza en la posicion -1,-1 (fuera del mapa), con una armadura, casco y arma
    // nula (osea posicion -1,-1)
    explicit Duck(int health);
    explicit Duck(int health, int id);

    // devuelve la posicion actual y setea la nueva posicion (tambien mueve la armadura, casco y
    // arma)
    void throw_weapon_to(Position position);
    Weapon& take_weapon(Weapon weapon);
    Armor& take_armor(Armor armor);
    Helmet& take_helmet(Helmet helmet);

    Weapon& get_weapon();
    Armor& get_armor();
    Helmet& get_helmet();

    bool is_alive();

    void receive_damage(int damage);
    ~Duck() {}
};
