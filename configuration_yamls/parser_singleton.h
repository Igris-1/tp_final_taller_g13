#ifndef PARSER_SINGLETON_H
#define PARSER_SINGLETON_H

#include "parser_yaml.h"

class ParserSingleton {
    private:
        static ParserYAML* instance;
        ParserSingleton();
        ParserSingleton(const ParserSingleton&) = delete;
        ParserSingleton& operator=(const ParserSingleton&) = delete;
    public:
        static ParserYAML* get_instance(){
            if(instance == nullptr){
                instance = new ParserYAML();
            }
            return instance;
        }
        void load_files(const std::string& map_file, const std::string& game_file);
        int get_value_game(const std::string& path);
        std::vector<std::tuple<int, int, int, int>> get_map_structure(std::string type_structure);
        std::vector<std::tuple<int, int>> get_spawn_points(std::string type_item);
        ~ParserSingleton();
};
ParserYAML* ParserSingleton::instance = nullptr;  // por lo que encontre en google esto es asi pq si

#endif // PARSER_SINGLETON_H