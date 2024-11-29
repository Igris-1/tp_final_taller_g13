#ifndef BOX_H
#define BOX_H

#define RESISTANCE 1

#include <cstdlib>
#include <ctime>

#include "DTOs.h"
#include "positionable.h"

#define NO_RESISTANCE 0
#define RESISTANCE 1

class Box: public Positionable {
private:
    int resistance ;

public:
    Box(Hitbox hitbox);
    Box(int x, int y, int width, int height);

    void receive_damage(int damage);
    bool is_destroyed();
    bool get_reward();
    box_DTO get_DTO();
};
#endif
