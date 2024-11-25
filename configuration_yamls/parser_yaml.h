#ifndef PARSER_YAML_H
#define PARSER_YAML_H

#include <iostream>
#include <fstream>
#include <string>
#include <yaml-cpp/yaml.h>
#include <stdexcept>
#include <memory>
#include <mutex>

class ParserYAML {
private:
    YAML::Node map_data;
    YAML::Node game_data;
    static std::mutex mtx;

public:
    ParserYAML() {}
    ParserYAML(const ParserYAML&) = delete;
    ParserYAML& operator=(const ParserYAML&) = delete;


    // Método para cargar los archivos YAML
    void load_files(const std::string& map_file, const std::string& game_file) {
        try {
            if(map_file != "")  map_data = YAML::LoadFile(map_file);
            if(game_file != "") game_data = YAML::LoadFile(game_file);
        } catch (const std::exception& e) {
            throw std::runtime_error(std::string("Error loading YAML files: ") + e.what());
        }
    }

    int get_value_game(const std::string& path) {
        std::istringstream stream(path);
        std::string word;
        YAML::Node current_node = this->game_data;

        while (stream >> word) {
            if (current_node[word]) {
                current_node = current_node[word]; // Navegamos al siguiente nodo
            } else {
                return -1; // Si alguna clave no existe
            }
        }

        if (current_node.IsScalar()) {
            return current_node.as<int>();
        }else {
            return -1;
        }
    }

    // type_structure puede ser "platforms" , "invalid positions"
    std::vector<std::tuple<int, int, int, int>> get_map_structure(std::string type_structure) {
        std::vector<std::tuple<int, int, int, int>> platforms;
        for (const auto& platform : this->map_data[type_structure]) {
            int x = platform["x"].as<int>();
            int y = platform["y"].as<int>();
            int width = platform["width"].as<int>();
            int height = platform["height"].as<int>();

            platforms.emplace_back(x, y, width, height);
        }
        return platforms;
    }

    std::vector<std::tuple<int, int>> get_spawn_points(std::string type_item) {
        std::vector<std::tuple<int, int>> items;
        for (const auto& platform : this->map_data[type_item]) {
            int x = platform["x"].as<int>();
            int y = platform["y"].as<int>();
            items.emplace_back(x, y);
        }
        return items;
    }


};

#endif // PARSER_YAML_H