#pragma once
#include "positionable.h"

class Weapon: public Positionable {
private:
    // cppcheck-suppress unusedStructMember
    int damage;

public:
    explicit Weapon(int damage);
    ~Weapon();
};
