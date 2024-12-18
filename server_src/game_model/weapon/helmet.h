#ifndef HELMET_H
#define HELMET_H

#include "../pickable.h"

class Helmet: public Pickable {
private:
public:
    explicit Helmet(int width, int height);
    void use() override;
    int get_id();
    weapon_DTO to_DTO() override;
    ~Helmet();
};

#endif
