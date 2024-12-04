#include "joinable_games_finder.h"

#include <cstdint>
#include <iostream>
#include <arpa/inet.h>

JoinableGamesFinder::JoinableGamesFinder(const char* host, const char* port): 
protocol(std::move(Socket(host, port))) {}

JoinableGamesFinder::~JoinableGamesFinder() {
}

std::vector<games_DTO> JoinableGamesFinder::ask_for_games() {
    std::vector<games_DTO> games;

    protocol.send_join_dummy_id();
    int size = protocol.receive_games_size();
    games.resize(size);
    
    for (int i = 0; i < size; i++) {
        games_DTO game = protocol.receive_games_dto();
        games[i] = game;
    }
    return games;
}