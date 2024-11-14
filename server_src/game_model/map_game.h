#ifndef MAP_H
#define MAP_H

#include <vector>
#include <map>
#include "positionable.h"
#include "duck.h"
#include <set>
#include <memory>
#include "../common_src/duck_DTO.h"
#include "weapon/bullets_strategy/bullet_interface.h"
#include "hitbox.h"


#ifndef NUEVO_MAPA
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
    bool can_move_hitbox(Hitbox hitbox, int dx, int dy);

    // ---------------------
    explicit MapGame(int width, int height);
    bool add_invalid_position(Hitbox hitbox);
    bool add_platform(Hitbox hitbox);
    bool set_duck_start_position(std::shared_ptr<Duck> duck, int x, int y);
    bool move_duck(std::shared_ptr<Duck> duck, int dx, int dy);
    std::vector<platform_DTO> get_platforms_DTO();
};
#endif




/*------- NUEVOOOOO MAPPAAAAAA -------------------------*/
#ifdef NUEVO_MAPA

class MapGame{
    private:
    int height;
    int width;
    std::set<Hitbox> invalid_positions;
    std::set<Hitbox> platforms;
    std::map<int, std::shared_ptr<Duck>> ducks;

    bool hitbox_in_range(Hitbox hitbox);
    bool position_is_valid(Hitbox hitbox);
    bool not_in_invalid_position(Hitbox hitbox);
    bool not_in_platforms(Hitbox hitbox);
    bool can_move_hitbox(Hitbox hitbox, int dx, int dy);
    bool move_relative_if_posible(int id, int dx, int dy);

    public:
    explicit MapGame(int width, int height);
    bool add_invalid_position(Hitbox hitbox);
    bool add_platform(Hitbox hitbox);
    bool duck_exist(int id);
    bool set_duck_start_position(std::shared_ptr<Duck> duck, int x, int y);
    bool duck_is_alive(int id);
    void respawn_ducks();
    void remove_duck(int id);

    std::vector<duck_DTO> get_duck_DTO_list();
    std::vector<platform_DTO> get_platforms_DTO();
    
    std::vector<int> get_live_duck_ids();
    std::vector<int> get_all_duck_ids();
    

    
    // ---------------------
    
    
    
    
    
};

class MapError: public std::exception {
private:
    std::string msg;

public:
    MapError(std::string msg): msg(msg) {}
    virtual const char* what() const noexcept override {
        return msg.c_str();
    }
};

#endif

#endif