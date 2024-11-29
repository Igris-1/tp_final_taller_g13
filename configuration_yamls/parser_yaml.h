#ifndef PARSER_YAML_H
#define PARSER_YAML_H

#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>

#include <yaml-cpp/yaml.h>

class ParserYAML {
private:
    std::string map_data;
    std::string game_data;
    static std::mutex mtx;

public:
    ParserYAML() {}
    ParserYAML(const ParserYAML&) = delete;
    ParserYAML& operator=(const ParserYAML&) = delete;


    // Método para cargar los archivos YAML
    void load_files(const std::string& map_file, const std::string& game_file) {
        this->map_data = map_file;
        this->game_data = game_file;
    }

    int get_value_game(const std::string& path) {
        std::istringstream stream(path);
        std::string key;
        YAML::Node current_node = YAML::LoadFile(this->game_data);

        while (std::getline(stream, key, '.')) {
            if (!current_node[key]) {
                throw std::runtime_error("Key '" + key + "' not found in path: " + path);
            }
            current_node = current_node[key];
        }

        if (current_node.IsScalar()) {
            return current_node.as<int>();
        } else {
            throw std::runtime_error("Value at path '" + path + "' is not scalar");
        }
    }

    int get_value_map(const std::string& path) {
        std::istringstream stream(path);
        std::string key;
        YAML::Node current_node = YAML::LoadFile(this->map_data);

        while (std::getline(stream, key, '.')) {
            if (!current_node[key]) {
                throw std::runtime_error("Key '" + key + "' not found in path: " + path);
            }
            current_node = current_node[key];
        }

        if (current_node.IsScalar()) {
            return current_node.as<int>();
        } else {
            throw std::runtime_error("Value at path '" + path + "' is not scalar");
        }
    }

    // type_structure puede ser "platforms" , "invalid positions"
    std::vector<std::tuple<int, int, int, int>> get_map_structure(std::string type_structure) {
        std::vector<std::tuple<int, int, int, int>> platforms;
        for (const auto& platform: YAML::LoadFile(this->map_data)[type_structure]) {
            int x = platform["x"].as<int>();
            int y = platform["y"].as<int>();
            int width = platform["width"].as<int>();
            int height = platform["height"].as<int>();

            platforms.emplace_back(x, y, width, height);
        }
        return platforms;
    }
};

#endif  // PARSER_YAML_H