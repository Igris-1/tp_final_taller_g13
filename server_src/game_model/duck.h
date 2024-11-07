#ifndef DUCK_H 
#define DUCK_H

#include "armor.h"
#include "helmet.h"
#include "positionable.h"
#include "weapon/weapon.h"
#include "../../common_src/duck_DTO.h"

#define DUCK_WIDTH 32
#define DUCK_HEIGHT 48

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
    int get_health();
    int get_id();

    bool is_alive();
    bool is_this_duck(int id);
    void receive_damage(int damage);
    Hitbox get_hitbox();

    /*  devuelve los estados internos del duck en un dto (vida, id, posicion). 
        no sabe nada de estados de jumping, running, ni nada*/
    duck_DTO to_DTO();
    ~Duck() {}
};

#endif
