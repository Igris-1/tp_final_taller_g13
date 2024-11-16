#ifndef MAP_H
#define MAP_H

#include <map>
#include <memory>
#include <set>
#include <vector>

#include "../common_src/duck_DTO.h"
#include "weapon/bullets_strategy/bullet_interface.h"

#include "duck.h"
#include "hitbox.h"
#include "positionable.h"

#define NUEVO_MAPA

#ifndef NUEVO_MAPA
class MapGame {
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

#define HEALTH 100
#define RIGHT_DIRECTION 1
#define LEFT_DIRECTION -1
#define NO_DIRECTION 0
#define GRAVITY 1
#define JUMP_DIRECTION -1

class MapGame {
private:
    int height;
    int width;
    std::set<Hitbox> invalid_positions;
    std::set<Hitbox> platforms;
    std::map<int, std::shared_ptr<Duck>> ducks;
    std::map<int, std::shared_ptr<Duck>> ducks_dead;
    std::list<std::shared_ptr<Weapon>> pickables;
    std::list<std::shared_ptr<BulletInterface>> bullets;

    bool hitbox_in_range(Hitbox hitbox);
    bool position_is_valid(Hitbox hitbox);
    bool not_in_invalid_position(Hitbox hitbox);
    bool not_in_platforms(Hitbox hitbox);
    bool can_move_hitbox(Hitbox hitbox, int dx, int dy);

public:
    explicit MapGame(int width, int height);

    // MAP STRUCTURE
    bool add_invalid_position(Hitbox hitbox);
    bool add_platform(Hitbox hitbox);

    // DUCKS
    bool duck_exist(int id);
    bool set_duck_start_position(int duck_id, int x, int y);
    bool duck_is_alive(int id);
    void respawn_ducks();
    void remove_duck(int id);
    bool move_relative_if_posible(int duck_id, int dx, int dy);
    void continue_fire_rate(int id);
    void use_item(int duck_id, bool right_direction);

    // BULLETS AND PICKABLE
    void bullets_next_movement();
    bool move_relative_if_posible(Hitbox& hitbox, int dx, int dy);
    void ducks_try_pick_up(int id_duck);
    void ducks_try_throw(int id_duck, bool right_direction);
    void add_weapon(std::shared_ptr<Weapon> new_weapon, int x, int y);
    void gravity_weapon();
    void inertia_weapon();

    // DTO
    std::vector<bullet_DTO> get_bullets_DTO_list();
    std::vector<duck_DTO> get_duck_DTO_list();
    std::vector<weapon_DTO> get_weapons_DTO_list();
    std::vector<platform_DTO> get_platforms_DTO();

    // MANAGE DUCKS
    std::list<std::shared_ptr<BulletInterface>>& get_bullets_list();
    std::vector<int> get_live_duck_ids();
    std::vector<int> get_all_duck_ids();
    void clean_map(); // tiene que recibir donde spawnea en un futuro

};

class MapError: public std::exception {
private:
    std::string msg;

public:
    MapError(std::string msg): msg(msg) {}
    virtual const char* what() const noexcept override { return msg.c_str(); }
};

#endif

#endif