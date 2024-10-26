#ifndef HELMET_H
#define HELMET_H

#include "positionable.h"
class Helmet: public Positionable {
private:
    // cppcheck-suppress unusedStructMember
    int defense;

public:
    explicit Helmet(int defense);
    ~Helmet() {}
};

#endif
