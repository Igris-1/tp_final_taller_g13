#ifndef MAP_H
#define MAP_H

#include <list>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include "../common_src/duck_DTO.h"
#include "weapon/bullets_strategy/bullet_interface.h"
#include "weapon/weapons_strategy/weapon.h"

#include "box.h"
#include "duck.h"
#include "hitbox.h"
#include "pickable.h"
#include "positionable.h"

#define HEALTH 20
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
    std::list<std::shared_ptr<Box>> boxes;
    std::set<Hitbox> platforms;
    std::map<int, std::shared_ptr<Duck>> ducks;
    std::map<int, std::shared_ptr<Duck>> ducks_dead;
    std::list<std::shared_ptr<Pickable>> pickables;
    std::list<std::shared_ptr<Pickable>> pickables_spawned;
    std::list<std::shared_ptr<BulletInterface>> bullets;

    bool hitbox_in_range(Hitbox hitbox, bool can_fall);
    bool position_is_valid(Hitbox hitbox, bool can_fall, bool to_stand);
    bool out_of_map(Hitbox hitbox);
    bool not_in_invalid_position(Hitbox hitbox, bool to_stand);
    bool not_in_platforms(Hitbox hitbox, bool to_stand);
    bool not_in_boxes(Hitbox hitbox, bool to_stand);
    bool can_move_hitbox(Hitbox hitbox, int dx, int dy, bool can_fall);
    // bool can_move_hitbox_without_boxes(Hitbox hitbox, int dx, int dy);

public:
    explicit MapGame(int width, int height);

    // MAP STRUCTURE
    bool add_invalid_position(Hitbox hitbox); 
    bool add_platform(Hitbox hitbox);
    bool add_box(Hitbox hitbox);
    bool already_exist_a_pickable(int x, int y);
    void approximate_spawn_to_platform(int x, int& y, int width, int height, bool is_item);
    bool change_hitbox_size(Hitbox& hitbox, int width, int height, bool to_stand);

    // DUCKS
    bool duck_exist(int id);
    bool set_duck_start_position(int duck_id, int x, int y);
    bool duck_is_alive(int id);
    void respawn_ducks(std::vector<std::tuple<int, int>> positions_to_respawn);
    void remove_duck(int id);
    bool move_relative_if_posible(int duck_id, int dx, int dy);
    void continue_fire_rate(int id);
    void use_item(int duck_id, bool right_direction, bool is_holding);
    bool crouch_duck(int id, bool crouch);
    // void keep_using_item(int duck_id, bool right_direction);

    // BULLETS AND PICKABLE
    void bullets_next_movement();
    bool move_relative_if_posible(Hitbox& hitbox, int dx, int dy);
    void ducks_try_pick_up(int id_duck);
    void throw_item(int duck_id, bool right_direction);
    void ducks_try_throw(int id_duck, bool right_direction);
    void add_item(std::shared_ptr<Pickable> new_weapon, int x, int y);
    void gravity_weapon();
    void inertia_weapon();

    // DTO
    std::vector<bullet_DTO> get_bullets_DTO_list();
    std::vector<duck_DTO> get_duck_DTO_list();
    std::vector<weapon_DTO> get_weapons_DTO_list();
    std::vector<platform_DTO> get_platforms_DTO();
    std::vector<box_DTO> get_boxes_DTO();

    // MANAGE DUCKS
    std::list<std::shared_ptr<BulletInterface>>& get_bullets_list();
    std::vector<int> get_live_duck_ids();
    std::vector<int> get_all_duck_ids();
    int ducks_dead_size();
    void clean_map(std::vector<std::tuple<int, int>> positions_to_respawn);  // tiene que recibir donde spawnea en un futuro
};

class MapError: public std::exception {
private:
    std::string msg;

public:
    MapError(std::string msg): msg(msg) {}
    virtual const char* what() const noexcept override { return msg.c_str(); }
};
#endif
