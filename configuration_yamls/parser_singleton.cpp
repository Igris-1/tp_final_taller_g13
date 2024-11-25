#include "parser_singleton.h"
        void ParserSingleton::load_files(const std::string& map_file, const std::string& game_file){
            instance->load_files(map_file, game_file);
        }
        int ParserSingleton::get_value_game(const std::string& path){
            return instance->get_value_game(path);
        }
        std::vector<std::tuple<int, int, int, int>> ParserSingleton::get_map_structure(std::string type_structure){
            return instance->get_map_structure(type_structure);
        }
        std::vector<std::tuple<int, int>> ParserSingleton::get_spawn_points(std::string type_item){
            return instance->get_spawn_points(type_item);
        }
        ParserSingleton::~ParserSingleton(){
            delete instance;
        }