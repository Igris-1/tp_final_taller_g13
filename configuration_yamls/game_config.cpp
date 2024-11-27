#include "game_config.h"

    GameConfig::GameConfig(const std::string& map_file, const std::string& game_file){
        ParserYAML parser;
        parser.load_files(map_file, game_file);

        // ducks config
        this->ducks_config.health = parser.get_value_game("ducks_config health");
        this->ducks_config.tiles_per_jump = parser.get_value_game("ducks_config tiles_per_jump");
        this->ducks_config.product_factor_jump = parser.get_value_game("ducks_config product_factor_jump");
        this->ducks_config.add_factor_jump = parser.get_value_game("ducks_config add_factor_jump");
        this->ducks_config.product_factor_gravity = parser.get_value_game("ducks_config product_factor_gravity");
        this->ducks_config.add_factor_gravity = parser.get_value_game("ducks_config add_factor_gravity");
        this->ducks_config.speed_of_game = parser.get_value_game("ducks_config speed_of_game");
        
        // weapons config
        std::vector<std::string> weapons_name = { "grenade", "banana", "pew_pew_laser", "laser_rifle", "ak_47", 
                                                "dueling_pistol", "cowboy_pistol", "magnum", "shotgun", "sniper"};

        for(auto weapon: weapons_name){
            weapon_config aux;
            aux.name = weapon;
            aux.shot = parser.get_value_game(weapon + " shot");
            aux.damage = parser.get_value_game(weapon + " damage");
            aux.recoil = parser.get_value_game(weapon + " recoil");
            aux.scope = parser.get_value_game(weapon + " scope");
            aux.reload_time = parser.get_value_game(weapon + " reload_time");
            aux.hitbox_width = parser.get_value_game(weapon + " hitbox_width");
            aux.hitbox_height = parser.get_value_game(weapon + " hitbox_height");   
            this->weapons_config[weapon] = aux;
        }

        // map config
        this->map_height = parser.get_value_map("map map_height");
        this->map_width = parser.get_value_map("map map_width");

        this->platforms = parser.get_map_structure("platforms");
        this->boxes = parser.get_map_structure("boxes");
        this->ducks_spawn = parser.get_map_structure("ducks_spawn");
        this->weapons_spawn = parser.get_map_structure("weapons_spawn");
    }

    const duck_config& GameConfig::get_duck_config(){
        return this->ducks_config;
    }

    const std::vector<std::tuple<int, int, int, int>>& GameConfig::get_item(const std::string& type){
        if(type == "boxes"){
            return this->boxes;
        }
        if(type == "platforms"){
            return this->platforms;
        }
        if(type=="ducks_spawn"){
            return this->ducks_spawn;
        }
        if(type=="weapons_spawn"){
            return this->weapons_spawn;
        }
        throw GameConfigError(type + " no existe en el yaml leido\n");
    }

    const weapon_config& GameConfig::get_weapon_config(const std::string& type){
        try{
            return this->weapons_config[type];
        }
        catch(const std::exception& e){
            throw GameConfigError(type + " no existe en las armas leidas\n");
        }
    }