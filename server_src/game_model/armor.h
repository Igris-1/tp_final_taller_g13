#pragma once

#include "positionable.h"
class Armor: public Positionable {
private:
    // cppcheck-suppress unusedStructMember
    int defense;

public:
    explicit Armor(int defense);
    ~Armor() {}
};
