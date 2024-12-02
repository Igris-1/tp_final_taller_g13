#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../../common_src/DTOs.h"
#include "../../common_src/game_snapshot_t.h"
#include "../../configuration_yamls/game_config.h"
#include "weapon/bullets_strategy/bullet_interface.h"
#include "weapon/weapon_factory.h"
#include "weapon/weapons_strategy/weapon.h"

#include "duck.h"
#include "map_game.h"

// movimientos laterales
#define RIGHT_MOVEMENT 1
#define LEFT_MOVEMENT -1

// movimientos verticales
#define GRAVITY 1
#define JUMP_DIRECTION -1

#define X_POSITION 0
#define Y_POSITION 1
#define WIDTH_POSITION 2
#define HEIGHT_POSITION 3

#define WEAPON_SPAWN_SIZE 40

// factores para el salto y gravedad

// #define TILES_FOR_JUMP 175
// #define PRODUCT_FACTOR_JUMP 2  // estos son re falopas, pero basicamente hace q la gravedad sea
// mas fuerte #define ADD_FACTOR_JUMP 3 #define PRODUCT_FACTOR_GRAVITY 2 #define ADD_FACTOR_GRAVITY
// 8
#define TIME_TO_RESPAWN 300

typedef struct {
    bool is_jumping = false;
    bool falling_with_style = false;

    int tiles_to_jump = 0;
    int air_time = 0;
    bool is_falling = false;
    int time_to_respawn = 0;

    bool is_moving_right = false;
    bool is_moving_left = false;

    bool facing_direction = true;  // true  -> derecha | false -> izquierda
    bool holding_action = false;

    bool crouching = false;
    bool trying_to_stand = false;
    bool looking_up = false;
    bool do_death_sound = true;

} duck_state;

class Game {
private:
    MapGame map;                                                   // el que sabe que se puede mover y que no              
    std::map<int, std::shared_ptr<duck_state>> ducks_states;    // tiene el estado de cada pato
    std::map<int, int> ducks_score;                             // tiene los puntos de cada pato
    std::vector<std::tuple<int, int>> spawn_positions;          // tiene las posiciones de spawn de armas
    std::vector<std::tuple<int, int>> spawn_ducks;              // tiene las posiciones de spawn de patos
    int actual_round; 
    int time_to_respawn;
    bool started_game;

    // yaml things
    const std::map<std::string, weapon_config> weapons_config;
    const duck_config ducks_config;

    // "defines" from yaml
    const int TILES_FOR_JUMP = 175;
    const int PRODUCT_FACTOR_JUMP = 2;
    const int ADD_FACTOR_JUMP = 3;
    const int PRODUCT_FACTOR_GRAVITY = 2;
    const int ADD_FACTOR_GRAVITY = 8;
    const int SPEED_OF_GAME = 10;

    // private methods, internal uses
    void duck_exist(int id);
    void gravity_movement(int id_duck);
    void jump_movement(int id_duck);
    void jump_with_style(int id_duck);
    void load_platforms(std::vector<std::tuple<int, int, int, int>>& spawns);
    void load_boxes(std::vector<std::tuple<int, int, int, int>>& spawns);
    void load_spawn_ducks(std::vector<std::tuple<int, int, int, int>>& spawns);
    void load_spawn_weapons(std::vector<std::tuple<int, int, int, int>>& spawns);
   

    // MAP FUNCTIONS
    void add_weapon_spawn_platform(Hitbox hitbox);
    void add_new_platform(Hitbox hitbox);
    void add_spawn_position(Hitbox hitbox);  // agrega una posicion de spawn de armas
    void add_spawn_duck(Hitbox hitbox);
    void add_box(Hitbox hitbox);

public:
    Game(GameConfig& config);

    // DUCK
    void set_duck_start_position(int id, int x, int y);
    void remove_duck(int id);
    void spawns_ducks_on_start_position();

    // RUN
    void run_duck(int duck_id, bool left, bool right);
    void stop_run_duck(int id, bool stop_left, bool stop_right);

    // MOVEMENTS
    void continue_horizontal_movements();
    void continue_vertical_movements();

    // JUMP and CROUCH
    void jump_duck(int id, bool jump);
    void stop_jump_duck(int id, bool stop_jump);
    void crouch_duck(int id, bool crouch);
    void stop_crouch_duck(int id, bool stop_crouch);

    // LOOK UP
    void duck_looks_up(int id, bool looking_up);
    void duck_stops_looking_up(int id, bool looking_up);

    //  ITEMS
    void use_duck_item(int id, bool fire);
    void keep_using_item();
    void stop_duck_item(int id, bool stop_fire);
    void pick_up_item(int id, bool pick_up);
    void throw_item(int id, bool throw_item);

    // DATA
    game_snapshot_t get_snapshot();
    std::vector<duck_DTO> get_duck_DTO_list();
    score_DTO get_score_DTO();
    map_structure_t get_map_structure();

    // MAP FUNCTIONS
    void load_configuration(GameConfig& config);

    // game logic
    void start_game();
    void reset_round(bool practice_mode);
    bool check_if_round_finished();
    bool check_if_winner();
    void random_item_spawn(bool on_game, bool lineal_spawn);
    void reset_death_sound();
};

class GameError: public std::exception {
private:
    std::string msg;

public:
    GameError(std::string msg): msg(msg) {}
    virtual const char* what() const noexcept override { return msg.c_str(); }
};

#endif
