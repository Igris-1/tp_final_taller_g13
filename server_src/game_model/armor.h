#pragma once

#include "positionable.h"
class Armor: public Positionable{
    private:
        int defense;
    public:
        Armor(int defense);
        ~Armor(){}
};
