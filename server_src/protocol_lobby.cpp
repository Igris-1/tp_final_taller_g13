#include "protocol_lobby.h"
#include <functional>
#include <arpa/inet.h>
#include <iostream>
#include "../common_src/translator_DTOs.h"

#define NO_MORE_MAPS 0x00
#define GET_GAMES 0x04
#define GET_PLAYERS 0x05
#define GET_MAPS 0x06
#define GET_MAX_PLAYERS 0x08
#define GET_MAP_NAME 0x09


ProtocolLobby::ProtocolLobby(Socket& socket):
    socket(socket), 
    socket_is_closed(false){
}

ProtocolLobby::~ProtocolLobby(){}

int ProtocolLobby::receive_key_code(){
    int key_code;
    socket.recvall(&key_code, sizeof(uint8_t), &socket_is_closed);
    return key_code;
}

void ProtocolLobby::send_games_size(int& size){
    uint8_t code = GET_GAMES;
    socket.sendall(&code, sizeof(uint8_t), &socket_is_closed);
    int size_to_send = htons(size);
    socket.sendall(&size_to_send, TWO_BYTES, &socket_is_closed);
}

void ProtocolLobby::send_games(games_DTO& game_dto){
    TranslatorDTOs translator_games;
    translator_games.hton_games_DTO(&game_dto);
    socket.sendall(&game_dto, sizeof(games_DTO), &socket_is_closed);
}


void ProtocolLobby::stop_sending_maps(){
    uint8_t code = NO_MORE_MAPS;
    socket.sendall(&code, sizeof(uint8_t), &socket_is_closed);
}

void ProtocolLobby::send_text(const std::string& text) {
    if (socket_is_closed) {
        return;
    }
    uint8_t length = text.size();
    //uint8_t bits_to_be_send = htons(static_cast<uint16_t>(length));
    socket.sendall(&length, sizeof(uint8_t), &socket_is_closed);
    socket.sendall(text.data(), text.size(), &socket_is_closed);
}

void ProtocolLobby::send_number(uint8_t& number) {
    uint8_t buffer = number;
    socket.sendall(&buffer, sizeof(uint8_t), &socket_is_closed);
}

int ProtocolLobby::get_players(){
    int players = 0;
    uint8_t code = GET_PLAYERS;
    socket.sendall(&code, sizeof(uint8_t), &socket_is_closed);
    socket.recvall(&players, sizeof(uint8_t), &socket_is_closed);
    return players;
}

int ProtocolLobby::get_game_id(){
    uint8_t code = 0x06;
    socket.sendall(&code, sizeof(uint8_t), &socket_is_closed);
    uint8_t game_id;
    socket.recvall(&game_id, sizeof(uint8_t), &socket_is_closed);
    return game_id;
}


int ProtocolLobby::get_max_players(){
    int max_players;
    uint8_t code = GET_MAX_PLAYERS;
    socket.sendall(&code, sizeof(uint8_t), &socket_is_closed);
    socket.recvall(&max_players, sizeof(uint8_t), &socket_is_closed);
    return max_players;
}

std::string ProtocolLobby::receive_map_name(){
    uint8_t code = GET_MAP_NAME;
    socket.sendall(&code, sizeof(uint8_t), &socket_is_closed);
    uint8_t size;
    socket.recvall(&size, sizeof(uint8_t), &socket_is_closed);

    std::string namebuffer;
    namebuffer.resize(size);
    socket.recvall(&namebuffer[0], size, &socket_is_closed);
    return namebuffer;
}


