#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <string>
#include <vector>
#include <map>
#include "parser_yaml.h"

typedef struct{
    std::string name;
    int shot;
    int damage;
    int recoil;
    int scope;
    int reload_time;
    int hitbox_width;
    int hitbox_height;
} weapon_config;

typedef struct{
    int health;
    int tiles_per_jump;
    int product_factor_jump;
    int add_factor_jump;
    int product_factor_gravity;
    int add_factor_gravity;
    int speed_of_game;
} duck_config;

class GameConfig{
    private:
        // map configuration
        int map_width;
        int map_height;
        
        // map spawns
        std::vector<std::tuple<int, int, int, int>> boxes;
        std::vector<std::tuple<int, int, int, int>> platforms;
        std::vector<std::tuple<int, int, int, int>> ducks_spawn;
        std::vector<std::tuple<int, int, int, int>> weapons_spawn;

        // game configurations
        std::map<std::string, weapon_config> weapons_config;
        duck_config ducks_config;        
        
    public:
        GameConfig(const std::string& map_file, const std::string& game_file);
        const duck_config& get_duck_config();
        const std::vector<std::tuple<int, int, int, int>>& get_item(const std::string& type);
        const weapon_config&  get_weapon_config(const std::string& type);
        void print();
};

class GameConfigError: public std::exception {
private:
    std::string msg;

public:
    GameConfigError(std::string msg): msg(msg) {}
    virtual const char* what() const noexcept override { return msg.c_str(); }
};

#endif