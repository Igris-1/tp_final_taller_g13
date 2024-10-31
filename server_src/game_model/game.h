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
#include "duck_DTO.h"
#include "../../common_src/game_snapshot_t.h"

#define MOVEMENT 15

typedef struct{
    //Position relative_movement = Position(0,0);
    bool is_jumping = false;
    int tiles_to_jump = 0;
    bool is_running = false;
    
    bool moving_right = false;
    bool moving_left = false; 

    bool is_shooting = false;
}duck_state;

class Game {
    private:
        int id;
        std::map<int, std::shared_ptr<duck_state>> ducks_states;
        MapGame map;
        std::map<int, std::shared_ptr<Duck>> ducks;
    public:
        Game(int high, int width);
        
        int add_duck(int health, int id);
        void remove_duck(int id);
        Position position_duck(int id);
        void move_duck(int id, Position movement);
        void run_duck(int id, Position movement);
        void set_duck_start_position(int id, Position position);
        void stop_run_duck(int id);
        void continue_movements();
        void jump_duck(int id, int jump_size);

        void add_invalid_position(Position position);

        std::vector<duck_DTO> get_duck_DTO_list();
        game_snapshot_t get_snapshot();
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
