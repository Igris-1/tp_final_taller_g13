#ifndef BANANA_H
#define BANANA_H

#include <vector>

#include "../pickable.h"


class Banana: public Pickable {

private:
    bool active = false;

public:
    Banana(int width, int height);
    void use();
    int get_id() override;
    bool is_active() override;
    bool is_banana() override;
    weapon_DTO to_DTO() override;
    ~Banana();
};


#endif  // BANANA_H