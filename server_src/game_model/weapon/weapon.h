#ifndef WEAPON_H
#define WEAPON_H

#include "../positionable.h"

class Weapon: public Positionable {
protected:
    // cppcheck-suppress unusedStructMember
    int damage;
    

public:
    explicit Weapon(int damage);
    virtual bool is_fake() { return false; }
    ~Weapon(){}
};

#endif
