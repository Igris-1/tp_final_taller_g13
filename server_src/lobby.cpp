#include "lobby.h"

#include <filesystem>
#include <string>
#include <functional>


#define SHUT_DOWN_TWO 2
#define NEW_GAME 0
#define JOIN_GAME 1
#define JOIN_TO_RANDOM_GAME 3
#define ASK_FOR_GAMES 2
#define PRACTICE_GAME 4
#define ASK_FOR_MAPS 5
#define NEW_GAME_CUSTOM 6

namespace fs = std::filesystem;

Lobby::Lobby(GamesManager& games_manager, Socket&& socket)
    : games_manager(games_manager),
      socket(std::move(socket)) {}

void Lobby::creating_game(bool custom_map){
    bool aux = true;
    uint8_t code2 = 0x05;
    uint8_t buffer;
    socket.sendall(&code2, ONE_BYTE, &aux);
    socket.recvall(&buffer, ONE_BYTE, &aux);
    uint8_t code = 0x08;
    uint8_t  maxplayers;
    socket.sendall(&code, ONE_BYTE, &aux);
    socket.recvall(&maxplayers, ONE_BYTE, &aux);
    if(!custom_map){
        if(!this->games_manager.create_new_game(std::move(socket), buffer, (int)maxplayers)){
            std::cout << "Error creating game" << std::endl;
        }
        return;
    }
    std::string map_name;
    code = 0x09;
    this->socket.sendall(&code, ONE_BYTE, &aux);
    uint8_t buffer2;
    this->socket.recvall(&buffer2, ONE_BYTE, &aux);
    std::string namebuffer;
    namebuffer.resize(buffer2);
    this->socket.recvall(&namebuffer[0], buffer2, &aux);
    map_name = std::string(namebuffer);
    this->games_manager.create_new_custom_game(std::move(socket), buffer, (int)maxplayers, map_name);
}

bool Lobby::ask_for_maps(bool& is_close){
    const fs::path directory_path = "../maps";
        try {
            if (fs::exists(directory_path) && fs::is_directory(directory_path)) {
                for (const auto& entry : fs::directory_iterator(directory_path)) {
                    std::string relative_path = entry.path().filename().string();     
                    size_t stop_pos = relative_path.find('.');
                    if (stop_pos != std::string::npos) {
                        relative_path = relative_path.substr(0, stop_pos);
                    }
                    uint8_t size = relative_path.size();
                    socket.sendall(&size, ONE_BYTE, &is_close);
                    socket.sendall(relative_path.c_str(), size, &is_close);
                }
                uint8_t zero = 0;
                socket.sendall(&zero, ONE_BYTE, &is_close);
            } else {
                return false;
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Filesystem error: " << e.what() << '\n';
            return true;
        }
        return true;
}

bool Lobby::join_random_game(bool& is_close){
    try {
            uint8_t code2 = 0x05;
            socket.sendall(&code2, ONE_BYTE, &is_close);
            uint8_t buffer2;
            socket.recvall(&buffer2, ONE_BYTE, &is_close);
            if(!this->games_manager.add_client_to_random_game(std::move(socket), buffer2)){
                std::cout << "Error joining game" << std::endl;
            }
        } catch (const GamesManagerError& e) {
            return false;
        }
    return true;
}

bool Lobby::join_game(bool& is_close){
    uint8_t code = 0x06;
    socket.sendall(&code, ONE_BYTE, &is_close);
    uint8_t buffer;
    socket.recvall(&buffer, ONE_BYTE, &is_close);
    uint8_t buffer2;
    socket.recvall(&buffer2, ONE_BYTE, &is_close);
    if(!this->games_manager.add_client_to_game(buffer2, std::move(socket), buffer)){
        return false;
    }
    return true;
}

bool Lobby::ask_for_games(bool& is_close){
    std::list<std::unique_ptr<game_t>>& games = this->games_manager.get_games();
    uint16_t size = games.size();
    uint8_t code = 0x04;
    socket.sendall(&code, ONE_BYTE, &is_close);
    size = htons(size);
    socket.sendall(&size, TWO_BYTES, &is_close);
    for (auto& game: games) {
        games_DTO game_dto;
        game_dto.game_id = game->game_id;
        game_dto.current_players = game->player_count;
        game_dto.max_players = game->max_players;
        TranslatorDTOs translator_games;
        translator_games.hton_games_DTO(&game_dto);
        socket.sendall(&game_dto, sizeof(games_DTO), &is_close);
    }
    return true;
}

void Lobby::run() {
    std::map<uint8_t, std::function<void(bool&)>> actions = {
            {NEW_GAME, [&](bool& is_close) { creating_game(false); }},
            {JOIN_TO_RANDOM_GAME, [&](bool& is_close) {
                if (!this->join_random_game(is_close)) {
                    socket.shutdown(SHUT_DOWN_TWO);
                    socket.close();
                }
            }},
            {JOIN_GAME, [&](bool& is_close) {
                if (!this->join_game(is_close)) {
                    std::cout << "Error joining game" << std::endl;
                }
            }},
            {ASK_FOR_GAMES, [&](bool& is_close) { this->ask_for_games(is_close); }},
            {PRACTICE_GAME, [&](bool& is_close) {
                this->games_manager.add_to_practice_game(std::move(socket));
            }},
            {ASK_FOR_MAPS, [&](bool& is_close) {
                if (!this->ask_for_maps(is_close)) {
                    std::cerr << "Path does not exist or is not a directory.\n";
                }
            }},
            {NEW_GAME_CUSTOM, [&](bool& is_close) { creating_game(true); }},
        };
try {
    uint8_t key_code = 0;
    bool is_close = false;
    socket.recvall(&key_code, ONE_BYTE, &is_close);
    if (actions.count(key_code)) {
            actions[key_code](is_close);
        } else {
            std::cerr << "Unknown code received: " << (int)key_code << std::endl;
        }
    } catch (const LibError& e) {
        std::cerr << "LibError: " << e.what() << std::endl;
    }
}

Lobby::~Lobby() {}