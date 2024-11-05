#ifndef GAME_H
#define GAME_H

#include <map>
#include "duck.h"
#include "position.h"
#include "weapon/weapon.h"
#include "map_game.h"
#include <memory>
#include <iostream>
#include <vector>
#include "../../common_src/duck_DTO.h"
#include "../../common_src/game_snapshot_t.h"

// movimientos laterales
#define RIGHT_MOVEMENT 1
#define LEFT_MOVEMENT -1

// movimientos verticales
#define GRAVITY 1
#define GRAVITY 1
#define JUMP_DIRECTION -1

// factores para el salto y gravedad
#define TILES_FOR_JUMP 175
#define PRODUCT_FACTOR_JUMP 2  // estos son re falopas, pero basicamente hace q la gravedad sea mas fuerte
#define ADD_FACTOR_JUMP 3
#define PRODUCT_FACTOR_GRAVITY 2
#define ADD_FACTOR_GRAVITY 8
#define ADD_FACTOR_SLOW_GRAVITY 8

typedef struct duck_state{
    bool is_jumping = false;
    bool falling_with_style = false;

    int tiles_to_jump = 0;
    int air_time = 0;
    bool is_falling = false;
    
    bool is_moving_right = false;
    bool is_moving_left = false; 

    bool is_shooting = false;
}duck_state;

class Game {
    private:
        std::map<int, std::shared_ptr<duck_state>> ducks_states;
        MapGame map;
        std::map<int, std::shared_ptr<Duck>> ducks;
    public:
        Game(int high, int width);
        
        int add_duck(int health, int id);
        void remove_duck(int id);
        Position position_duck(int id);
        void move_duck(int id, Position movement);
        
        void run_duck(int duck_id, bool left, bool right);
        void set_duck_start_position(int id, Position position);
        
        void stop_run_duck(int id, bool stop_left, bool stop_right);
        void continue_horizontal_movements(int count=1);
        void continue_vertical_movements(int count=1);
        
        void jump_duck(int id, bool jump);
        void stop_jump_duck(int id, bool stop_jump);

        void add_invalid_position(Position position);

        std::vector<duck_DTO> get_duck_DTO_list();
        game_snapshot_t get_snapshot();
        map_structure_t get_map_structure();
};

class GameError: public std::exception {
private:
    std::string msg;

public:
    GameError(std::string msg): msg(msg) {}
    virtual const char* what() const noexcept override {
        return msg.c_str();
    }
};
#endif
