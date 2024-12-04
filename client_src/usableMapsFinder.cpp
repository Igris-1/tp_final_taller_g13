#include "usableMapsFinder.h"

#include <cstdint>

UsableMapsFinder::UsableMapsFinder(const char* host, const char* port): 
    protocol(std::move(Socket(host, port))) {}

UsableMapsFinder::~UsableMapsFinder() {
}

std::vector<std::string> UsableMapsFinder::ask_for_maps(){
    std::vector<std::string> maps;

    protocol.send_find_map_dummy_id();

    int name_size;
    
    while(name_size != 0){
        name_size = protocol.read_number();

        if(name_size == 0){
            break;
        }
        
        std::string map_name = protocol.receive_map_name(name_size);
        maps.push_back(map_name);
    }
    return maps;
}