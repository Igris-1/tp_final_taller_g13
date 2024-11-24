#ifndef HELMET_H
#define HELMET_H

// #include "positionable.h"
#include "pickable.h"

class Helmet: public Pickable {
private:
public:
    explicit Helmet();
    void use() override;
    int get_id();
    weapon_DTO to_DTO() override;
    ~Helmet();
};

#endif
