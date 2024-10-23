#pragma once

#include "positionable.h"
class Helmet: public Positionable{
    private:
        int defense;
    public:
        Helmet(int defense);
        ~Helmet(){}
};
