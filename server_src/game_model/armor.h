#ifndef ARMOR_H
#define ARMOR_H
#include "positionable.h"
class Armor: public Positionable {
private:
    // cppcheck-suppress unusedStructMember

public:
    explicit Armor();
    ~Armor() {}
};

#endif
