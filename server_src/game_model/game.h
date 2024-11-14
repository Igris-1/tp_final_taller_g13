#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../../common_src/duck_DTO.h"
#include "../../common_src/game_snapshot_t.h"
#include "weapon/bullets_strategy/bullet_interface.h"
#include "weapon/weapons_strategy/weapon.h"
#include "weapon/weapons_strategy/weapon_factory.h"

#include "duck.h"
#include "map_game.h"


#ifndef NUEVO_MAPA
// movimientos laterales
#define RIGHT_MOVEMENT 1
#define LEFT_MOVEMENT -1

// movimientos verticales
#define GRAVITY 1
#define JUMP_DIRECTION -1

// factores para el salto y gravedad
#define TILES_FOR_JUMP 175
#define PRODUCT_FACTOR_JUMP \
    2  // estos son re falopas, pero basicamente hace q la gravedad sea mas fuerte
#define ADD_FACTOR_JUMP 3
#define PRODUCT_FACTOR_GRAVITY 2
#define ADD_FACTOR_GRAVITY 8

typedef struct duck_state {
    bool is_jumping = false;
    bool falling_with_style = false;

    int tiles_to_jump = 0;
    int air_time = 0;
    bool is_falling = false;

    bool is_moving_right = false;
    bool is_moving_left = false;

    // true  -> derecha | false -> izquierda
    bool facing_direction = true;
    bool is_shooting = false;

} duck_state;

class Game {
private:
    std::map<int, std::shared_ptr<duck_state>> ducks_states;
    MapGame map;
    std::map<int, std::shared_ptr<Duck>> ducks;
    std::list<std::shared_ptr<BulletInterface>> bullets;
    std::list<std::shared_ptr<Weapon>> weapons_on_map;
    // std::list<std::shared_ptr<Armor>> armours_on_map;

    void duck_exist(int id);

public:
    Game(int high, int width);

    int add_duck(int health, int id);
    void remove_duck(int id);
    // Position position_duck(int id);

    void run_duck(int duck_id, bool left, bool right);
    void set_duck_start_position(int id, int x, int y);

    void stop_run_duck(int id, bool stop_left, bool stop_right);
    void continue_horizontal_movements(int count = 1);
    void continue_vertical_movements(int count = 1);

    void jump_duck(int id, bool jump);
    void stop_jump_duck(int id, bool stop_jump);

    void fire_duck_weapon(int id, bool fire);
    void keep_shooting();
    void stop_duck_weapon(int id, bool stop_fire);

    void pick_up_item(int id, bool pick_up);

    void add_invalid_position(Hitbox hitbox);
    void add_new_platform(Hitbox hitbox);
    //void add_weapon_on_map(std::string type_weapon, int x, int y);

    void respawner();

    std::vector<duck_DTO> get_duck_DTO_list();
    std::vector<bullet_DTO> get_bullet_DTO_list();
    std::vector<weapon_DTO> get_weapon_DTO_list();
    game_snapshot_t get_snapshot();
    map_structure_t get_map_structure();
};

class GameError: public std::exception {
private:
    std::string msg;

public:
    GameError(std::string msg): msg(msg) {}
    virtual const char* what() const noexcept override { return msg.c_str(); }
};
#endif


/*  ---------- NUEVOOOOO GAMEEE ----------------------------------*/
#ifdef NUEVO_MAPA

// movimientos laterales
#define RIGHT_MOVEMENT 1
#define LEFT_MOVEMENT -1

// movimientos verticales
#define GRAVITY 1
#define JUMP_DIRECTION -1

// factores para el salto y gravedad
#define TILES_FOR_JUMP 175
#define PRODUCT_FACTOR_JUMP \
    2  // estos son re falopas, pero basicamente hace q la gravedad sea mas fuerte
#define ADD_FACTOR_JUMP 3
#define PRODUCT_FACTOR_GRAVITY 2
#define ADD_FACTOR_GRAVITY 8

typedef struct {
    bool is_jumping = false;
    bool falling_with_style = false;

    int tiles_to_jump = 0;
    int air_time = 0;
    bool is_falling = false;

    bool is_moving_right = false;
    bool is_moving_left = false;

    // true  -> derecha | false -> izquierda
    bool facing_direction = true;
    bool is_shooting = false;

} duck_state;

class Game {
private:
    std::map<int, std::shared_ptr<duck_state>> ducks_states;
    MapGame map;

    void duck_exist(int id);

public:
    Game(int high, int width);


    // DUCK
    void set_duck_start_position(int id, int x, int y);
    void respawner();
    void remove_duck(int id);

    // RUN
    void run_duck(int duck_id, bool left, bool right);
    void stop_run_duck(int id, bool stop_left, bool stop_right);

    // MOVEMENTS
    void continue_horizontal_movements(int count = 1);
    void continue_vertical_movements(int count = 1);

    // JUMP
    void jump_duck(int id, bool jump);
    void stop_jump_duck(int id, bool stop_jump);

    //  WEAPONS
    void fire_duck_weapon(int id, bool fire);
    void keep_shooting();
    void stop_duck_weapon(int id, bool stop_fire);
    void pick_up_item(int id, bool pick_up);

    // DATA
    game_snapshot_t get_snapshot();
    std::vector<duck_DTO> get_duck_DTO_list();
    map_structure_t get_map_structure();

    // MAP FUNCTIONS
    void add_invalid_position(Hitbox hitbox);
    void add_new_platform(Hitbox hitbox);
    void add_weapon_on_map(std::string type_weapon, int x, int y);
};

class GameError: public std::exception {
private:
    std::string msg;

public:
    GameError(std::string msg): msg(msg) {}
    virtual const char* what() const noexcept override { return msg.c_str(); }
};

#endif
#endif
