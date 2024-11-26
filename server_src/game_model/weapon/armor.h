#ifndef ARMOR_H
#define ARMOR_H

#include "../pickable.h"


class Armor: public Pickable {
private:
public:
    explicit Armor(int width, int height);
    void use(MapGame& map);
    int get_id();
    weapon_DTO to_DTO() override;
};

#endif