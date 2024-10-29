#ifndef MAP_H
#define MAP_H

#include <vector>
#include "positionable.h"
#include "duck.h"
#include <set>
#include <memory>

class MapGame{
    private:
    int high;
    int width;
    std::set<Position> invalid_positions;

    bool position_in_range(Position position);
    bool position_is_valid(Position position);

    public:
    explicit MapGame(int high, int width);
    bool add_invalid_position(Position position);
    bool move_duck(std::shared_ptr<Duck> duck, Position movement);
};

#endif