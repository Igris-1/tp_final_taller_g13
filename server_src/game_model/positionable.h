#ifndef POSITIONABLE_H
#define POSITIONABLE_H

#include "hitbox.h"

#define DEFAULT_WIDTH 10
#define DEFAULT_HEIGHT 10
#define DEFAULT_X -1
#define DEFAULT_Y -1

class Positionable {
protected:
    Hitbox hitbox;

public:
    Positionable(Hitbox& Hitbox);
    Positionable(int x, int y, int width, int height);
    Positionable();
    void move_relative_to(int dx, int dy);
    void move_to(int x, int y);
    int get_x();
    int get_y();
    Hitbox get_hitbox();
    Hitbox& get_reference_hitbox();
    int get_width();
    int get_height();
};

#endif
