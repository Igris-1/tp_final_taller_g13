#include "usableMapsFinder.h"

#include <cstdint>

UsableMapsFinder::UsableMapsFinder(const char* host, const char* port): socket(host, port) {}

UsableMapsFinder::~UsableMapsFinder() {
    this->socket_is_closed = true;
    this->socket.close();
}

std::vector<std::string> UsableMapsFinder::ask_for_maps(){

    std::vector<std::string> maps;

    uint8_t num = 5;
    this->socket.sendall(&num, ONE_BYTE, &socket_is_closed);
    while(num != 0){
        this->socket.recvall(&num, ONE_BYTE, &socket_is_closed);
        if(num == 0){
            break;
        }
        char buffer [num+1];
        this->socket.recvall(buffer, num, &socket_is_closed);
        
        buffer[num] = '\0';
        std::string map_name(buffer);
        maps.push_back(map_name);
    }
    for(auto& map: maps){
        std::cout << map << std::endl;
    }
    return maps;
}