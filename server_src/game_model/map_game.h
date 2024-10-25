#ifndef MAP_H
#define MAP_H

#include <vector>
#include "positionable.h"
#include "duck.h"

class MapGame{
    private:
    int high;
    int width;
    std::vector<Positionable> positionables;

    public:
    explicit MapGame(int high, int width);
    bool add(Positionable object);
    bool move_positionable(Positionable duck, Position movement);
};

#endif