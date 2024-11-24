#ifndef BOX_H
#define BOX_H

#define RESISTANCE 10

#include "positionable.h"
#include <cstdlib>
#include <ctime> 
#include "duck_DTO.h"

class Box: public Positionable{
    private:
    int resistance;

    public:
    Box(Hitbox hitbox);
    Box(int x, int y, int width, int height);

    void receive_damage(int damage);
    bool is_destroyed();
    bool get_reward();
    box_DTO get_DTO();

};
#endif
