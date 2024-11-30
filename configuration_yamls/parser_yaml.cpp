#include "parser_yaml.h"

void ParserYAML::load_files(const std::string& map_file, const std::string& game_file) {
        this->map_data = map_file;
        this->game_data = game_file;
}

int ParserYAML::get_value_game(const std::string& path) {
        std::istringstream stream(path);
        std::string key;
        YAML::Node current_node = YAML::LoadFile(this->game_data);

        while (std::getline(stream, key, '.')) {
            if (!current_node[key]) {
                throw std::runtime_error("Key: " + key + " no existe en path : " + path);
            }
            current_node = current_node[key];
        }

        if (current_node.IsScalar()) {
            return current_node.as<int>();
        } else {
            throw std::runtime_error("el valor en " + path + " no es un numero");
        }
    }

int ParserYAML::get_value_map(const std::string& path) {
        std::istringstream stream(path);
        std::string key;
        YAML::Node current_node = YAML::LoadFile(this->map_data);

        while (std::getline(stream, key, '.')) {
            if (!current_node[key]) {
                throw std::runtime_error("Key: " + key + " no existe en path : " + path);
            }
            current_node = current_node[key];
        }

        if (current_node.IsScalar()) {
            return current_node.as<int>();
        } else {
            throw std::runtime_error("el valor en " + path + " no es un numero");
        }
    }

    std::vector<std::tuple<int, int, int, int>> ParserYAML::get_map_structure(std::string type_structure) {
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