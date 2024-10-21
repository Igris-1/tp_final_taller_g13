#pragma once
#include "Equipment.h"

//de esta clase van a heredar todas las guns.
//las granadas van a heredar de la clase explosive, q tiene atributos distintos
class Explosive : public Equipment{ 

    private:
        int damage;
        int range;


    virtual void removePin();

    public:
        virtual void action() = 0; // action tiene q llamar a removePin
        virtual void throw_equipment() = 0;
        virtual ~Explosive() = default;
};