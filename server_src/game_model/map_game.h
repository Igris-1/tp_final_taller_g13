#ifndef MAP_H
#define MAP_H

#include <vector>
#include "positionable.h"
#include "duck.h"
#include <set>

class MapGame{
    private:
    int high;
    int width;
    std::vector<Duck> ducks;
    std::set<Position> invalid_positions;
    std::vector<Positionable> guns_and_boxes;

    bool position_in_range(Position position);
    bool position_is_valid(Position position);

    public:
    explicit MapGame(int high, int width);
    bool add_duck(Duck duck);
    bool add_invalid_position(Position position);
    bool move_duck(int duck_id, Position movement);
    bool add_gun_or_box(Positionable gun_or_box);
    std::vector<duck_DTO> get_duck_DTO_list();
};

#endif