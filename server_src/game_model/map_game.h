#ifndef MAP_H
#define MAP_H

#include <vector>
#include "positionable.h"
#include "duck.h"
#include <set>
#include <memory>
#include "../common_src/duck_DTO.h"
#include "weapon/bullets_strategy/bullet_interface.h"
#include "hitbox.h"

class MapGame{
    private:
    int height;
    int width;
    std::set<Hitbox> invalid_positions;
    std::set<Hitbox> platforms;

    // bool position_in_range(Position position);
    bool hitbox_in_range(Hitbox hitbox);
    bool position_is_valid(Hitbox hitbox);
    bool not_in_invalid_position(Hitbox hitbox);
    bool not_in_platforms(Hitbox hitbox);

    public:
    explicit MapGame(int width, int height);
    bool add_invalid_position(Hitbox hitbox);
    bool add_platform(Hitbox hitbox);
    bool set_duck_start_position(std::shared_ptr<Duck> duck, int x, int y);
    bool move_duck(std::shared_ptr<Duck> duck, int dx, int dy);
    bool can_move_hitbox(Hitbox hitbox, int dx, int dy);
    std::vector<platform_DTO> get_platforms_DTO();
};

#endif