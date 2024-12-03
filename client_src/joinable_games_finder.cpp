#include "joinable_games_finder.h"

#include <cstdint>
#include <iostream>
#include <arpa/inet.h>
#include "../common_src/translator_DTOs.h"


#define ONE_BYTE 1
#define TWO_BYTES 2

JoinableGamesFinder::JoinableGamesFinder(const char* host, const char* port): socket(host, port) {}
JoinableGamesFinder::~JoinableGamesFinder() {
    this->socket_is_closed = true;
    this->socket.close();
}

// void run();
// void stop(); // quizas no hace falta

std::vector<games_DTO> JoinableGamesFinder::ask_for_games() {
    // si lanza algun erro hay que meter esto en un try catch
    std::vector<games_DTO> games;

    uint8_t num = 2;
    this->socket.sendall(&num, ONE_BYTE, &socket_is_closed);
    uint8_t code;
    this->socket.recvall(&code, ONE_BYTE, &socket_is_closed);
    if (code != 0x04) {
        return games;
    }
    uint16_t size = 0;
    this->socket.recvall(&size, TWO_BYTES, &socket_is_closed);
    size = ntohs(size);
    games.resize(size);
    TranslatorDTOs translator;
    for (int i = 0; i < size; i++) {
        games_DTO game;
        this->socket.recvall(&game, sizeof(games_DTO), &socket_is_closed);
        translator.ntoh_games_DTO(&game);
        games[i] = game;
    }
    return games;
}