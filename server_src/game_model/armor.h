#ifndef ARMOR_H
#define ARMOR_H

// #include "positionable.h"
#include "pickable.h"


class Armor: public Pickable {
private:
public:
    explicit Armor();
    void use();
    int get_id();
    weapon_DTO to_DTO() override;
};

#endif