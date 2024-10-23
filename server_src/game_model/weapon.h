#pragma once
#include "positionable.h"

class Weapon: public Positionable{
    private:
        int damage;
    public:
        Weapon(int damage);
        ~Weapon();
};