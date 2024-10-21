#pragma once
#include "Equipment.h"
//armadura/casco heredan de  Armour
// propongo q la 'armadura' pase a llamarse vest (chaleco) para no mezclarse con esta clase abstracta

class Armour : public Equipment{ 

    private:
        int damage_reduction; // por enunciado tiene q ser = 1, pero creo q por enunciado tambn tiene q ser algo q se pueda cambiar
        virtual void equip()= 0;

    public:
        virtual void action() = 0; // action tiene q llamar a shoot
        virtual void throw_equipment() = 0;
        virtual ~Armour() = default;
};