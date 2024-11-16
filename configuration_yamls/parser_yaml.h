#ifndef PARSER_YAML_H
#define PARSER_YAML_H

#include <yaml-cpp/yaml.h>
#include <iostream>

class ParserYAML {
    private:
        ParserYAML() = default; 
        YAML::Node mapConfig;
        YAML::Node gameConfig; 
    public:
        static ParserYAML& getInstance() {
            static ParserYAML instance; // Instancia única
            return instance;
        }

        void loadConfigs(const std::string& mapPath, const std::string& gamePath) {
            try {
                mapConfig = YAML::LoadFile(mapPath);
                gameConfig = YAML::LoadFile(gamePath);
                std::cout << "Archivos cargados exitosamente.\n";
            } catch (const YAML::Exception& e) {
                std::cerr << "Error al cargar los archivos YAML: " << e.what() << "\n";
            }
        }

        int getValue(const std::string& key) const {
            try{
                return mapConfig[key].as<int>();
            } catch (const YAML::Exception& e) {
                try{
                    return gameConfig[key].as<int>();
                } catch (const YAML::Exception& e) {
                    std::cerr << "Error al obtener el valor de la clave '" << key << "': " << e.what() << "\n";
                    return -1;
                }
            }
        }
        ParserYAML(const ParserYAML&) = delete;
        ParserYAML& operator=(const ParserYAML&) = delete;
    };


#endif // PARSER_YAML_H