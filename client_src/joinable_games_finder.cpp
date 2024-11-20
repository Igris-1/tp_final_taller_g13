#include "joinable_games_finder.h"
#include <cstdint>
#include <iostream>

#define ONE_BYTE 1
#define TWO_BYTES 2

JoinableGamesFinder::JoinableGamesFinder(const char* host, const char* port):socket(host, port){

}
JoinableGamesFinder::~JoinableGamesFinder(){
    //hay q cerrar el socket del dummy
}
// void run();
// void stop(); // quizas no hace falta
std::vector <games_DTO> JoinableGamesFinder::ask_for_games(){
    
    std::vector <games_DTO> games;

    uint8_t num  = 2;
    this->socket.sendall(&num, ONE_BYTE, &socket_is_closed);
    uint8_t code;
    this->socket.recvall(&code, ONE_BYTE, &socket_is_closed);
    if(code != 0x04){
        return games;
    }
    uint16_t size = 0;
    this->socket.recvall(&size, TWO_BYTES, &socket_is_closed);
    games.resize(size);

    for(int i = 0; i < size; i++){
        games_DTO game;
        this->socket.recvall(&game, sizeof(games_DTO), &socket_is_closed);
        games[i] = game;
        std::cout << "game id: " << static_cast<int>(game.game_id) << std::endl;
    }
    return games;
}