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


typedef struct{
    Position relative_movement;
    bool is_jumping;
    bool is_running;
    bool is_shooting;
}duck_state;

class Game {
    private:
        int id;
        std::map<int, std::shared_ptr<duck_state>> ducks_states;
        MapGame map;
        std::map<int, std::shared_ptr<Duck>> ducks;
    public:
        Game(int high, int width);
        // crea el duck y lo agrega al juego. devuelve el id del duck creado
        //int add_duck(int health);
        int add_duck(int health, int id);
        void remove_duck(int id);
        Position position_duck(int id);
        void move_duck(int id, Position movement);
        void run_duck(int id, Position movement);
        void set_duck_start_position(int id, Position position);
        void stop_duck(int id);
        void continue_movements();
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
