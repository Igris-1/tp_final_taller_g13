#ifndef MAP_H
#define MAP_H

#include <vector>
#include "positionable.h"
#include "duck.h"
#include <set>
#include <memory>

class MapGame{
    private:
    int height;
    int width;
    std::set<Position> invalid_positions;

    bool position_in_range(Position position);
    bool position_is_valid(Position position);

    public:
    explicit MapGame(int width, int height);
    bool add_invalid_position(Position position);
    bool set_duck_start_position(std::shared_ptr<Duck> duck, Position position);
    bool move_duck(std::shared_ptr<Duck> duck, Position movement);
};

#endif