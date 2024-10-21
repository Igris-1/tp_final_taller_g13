#pragma once
#include "Equipment.h"


//de esta clase van a heredar todas las guns.
//las granadas van a heredar de la clase explosive, q tiene atributos distintos
class Weapon : public Equipment{ 

    private:
    int initial_ammo; //solo hace falta si las armas se pueden recargar, cosa que creo q no se puede, pero por ahora lo dejo
    int ammo;
    int damage_per_shot;
    int range;
    virtual void shoot()= 0;

    public:
    virtual void action() = 0; // action tiene q llamar a shoot
    virtual void throw_equipment() = 0;
    virtual ~Weapon() = default;
};