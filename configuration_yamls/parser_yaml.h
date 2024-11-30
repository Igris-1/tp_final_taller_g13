#ifndef PARSER_YAML_H
#define PARSER_YAML_H

#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include <yaml-cpp/yaml.h>

class ParserYAML {
private:
    std::string map_data;
    std::string game_data;

public:
    ParserYAML() {}
    ParserYAML(const ParserYAML&) = delete;
    ParserYAML& operator=(const ParserYAML&) = delete;

    // para cargar los archivos YAML
    void load_files(const std::string& map_file, const std::string& game_file);

    int get_value_game(const std::string& path);

    int get_value_map(const std::string& path);

    // type_structure puede ser "platforms" , "weapons_spawns", "ducks_spawns", "boxes"
    std::vector<std::tuple<int, int, int, int>> get_map_structure(std::string type_structure);
};

#endif  // PARSER_YAML_H