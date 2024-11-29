#ifndef MAP_H
#define MAP_H

#include <list>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include "../common_src/DTOs.h"
#include "weapon/bullets_strategy/bullet_interface.h"
#include "weapon/weapons_strategy/weapon.h"

#include "box.h"
#include "duck.h"
#include "hitbox.h"
#include "pickable.h"
#include "positionable.h"

#define RIGHT_DIRECTION 1
#define LEFT_DIRECTION -1
#define NO_DIRECTION 0
#define UP_DIRECTION -1
#define GRAVITY 1
#define JUMP_DIRECTION -1

#define NOT_OWNER -2

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
    std::list<std::shared_ptr<Pickable>> explosives;
    sounds_DTO sounds;

    const int HEALTH = 20;

    // functions of structures
    bool hitbox_in_range(Hitbox hitbox, bool can_fall);
    bool position_is_valid(Hitbox hitbox, bool can_fall, bool to_stand);
    bool out_of_map(Hitbox hitbox);
    bool not_in_invalid_position(Hitbox hitbox, bool to_stand);
    bool not_in_platforms(Hitbox hitbox, bool to_stand);
    bool not_in_boxes(Hitbox hitbox, bool to_stand);

    // functions of movements
    bool can_move_hitbox(Hitbox hitbox, int dx, int dy, bool can_fall);
    bool approximate_spawn_to_platform(Hitbox& hitbox, bool is_item);

    // internal functions
    bool apply_recoil(std::shared_ptr<Duck> duck, int duck_id);
    bool apply_sliding(std::shared_ptr<Duck> duck, int duck_id);
    bool apply_movement(std::shared_ptr<Duck> duck, int duck_id, int& remaining_dx,
                        int& remaining_dy, int& x_step, int& y_step);
    void explosive_gravity(std::shared_ptr<Pickable> explosive);
    void inertial_classic_pickable(std::shared_ptr<Pickable> Pickable);
    void inertial_explosive_pickable(std::shared_ptr<Pickable> explosive);
    void duck_collision_explosive(std::__cxx11::list<std::shared_ptr<Pickable>>::iterator& explosive, bool& banana_flag);
    void grenade_exploted(std::__cxx11::list<std::shared_ptr<Pickable>>::iterator& explosive);
    bool bullet_collision_box(std::shared_ptr<Box>& box, std::__cxx11::list<std::shared_ptr<BulletInterface>>::iterator& bullet, const std::map<std::string, weapon_config>& weapons_config);

public:
    explicit MapGame(int width, int height, int health);
    int get_width();
    int get_height();

    // MAP STRUCTURE
    bool add_invalid_position(Hitbox hitbox);
    bool add_platform(Hitbox hitbox);
    bool add_box(Hitbox hitbox);
    bool already_exist_a_pickable(int x, int y);
    bool change_hitbox_size(Hitbox& hitbox, int width, int height, bool to_stand);

    // DUCKS
    bool duck_exist(int id);
    bool set_duck_start_position(int duck_id, int x, int y);
    bool duck_is_alive(int id);
    void respawn_ducks(std::vector<std::tuple<int, int>> positions_to_respawn);
    void remove_duck(int id);
    bool move_relative_if_posible(int duck_id, int dx, int dy);
    void continue_fire_rate(int id);
    void use_item(int duck_id, bool right_direction, bool is_holding, bool looking_up);
    bool crouch_duck(int id, bool crouch);
    // void keep_using_item(int duck_id, bool right_direction);

    // BULLETS AND PICKABLE
    void bullets_next_movement(const std::map<std::string, weapon_config>& weapons_config);
    bool move_relative_if_posible(Hitbox& hitbox, int dx, int dy);
    void ducks_try_pick_up(int id_duck);
    void throw_item(int duck_id, bool right_direction, bool looking_up);
    void ducks_try_throw(int id_duck, bool right_direction);
    void add_item(std::shared_ptr<Pickable> new_weapon, int x, int y);
    void gravity_weapon();
    void inertia_weapon();
    void explosives_on_map();

    // DTO
    std::vector<bullet_DTO> get_bullets_DTO_list();
    std::vector<duck_DTO> get_duck_DTO_list();
    std::vector<weapon_DTO> get_weapons_DTO_list();
    std::vector<platform_DTO> get_platforms_DTO();
    std::vector<box_DTO> get_boxes_DTO();
    sounds_DTO get_sounds_DTO();
    void set_bullet_sound(int sound);

    // MANAGE DUCKS
    std::list<std::shared_ptr<BulletInterface>>& get_bullets_list();
    std::vector<int> get_live_duck_ids();
    std::vector<int> get_all_duck_ids();
    int ducks_dead_size();
    void clean_map(std::vector<std::tuple<int, int>>
                           positions_to_respawn);  // tiene que recibir donde spawnea en un futuro
};

class MapError: public std::exception {
private:
    std::string msg;

public:
    MapError(std::string msg): msg(msg) {}
    virtual const char* what() const noexcept override { return msg.c_str(); }
};
#endif
