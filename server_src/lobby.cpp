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

Lobby::Lobby(GamesManager& games_manager, Socket&& ss)
    : games_manager(games_manager),
      socket(std::move(ss)),
      protocol(socket) {}

void Lobby::creating_game(bool custom_map){
    int number_of_players = protocol.get_players();
    int max_players = protocol.get_max_players();

    if(!custom_map){
        this->games_manager.create_new_game(std::move(socket), number_of_players, max_players);
        return;
    }
    std::cout << "Creating custom game" << std::endl;
    std::string map_name = protocol.receive_map_name();
    std::cout << "despues de receive map" << std::endl;
    this->games_manager.create_new_custom_game(std::move(socket), number_of_players, max_players, map_name);
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
                    protocol.send_text(relative_path);
                }
                protocol.stop_sending_maps();
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
            int number_of_players = protocol.get_players();
            if(!this->games_manager.add_client_to_random_game(std::move(socket), number_of_players)){
                std::cout << "Error joining game" << std::endl;
            }
        } catch (const GamesManagerError& e) {
            return false;
        }
    return true;
}

bool Lobby::join_game(bool& is_close){
    uint8_t number_of_players = protocol.get_players();
    int game_id = protocol.get_game_id();
    if(!this->games_manager.add_client_to_game(game_id, std::move(socket), number_of_players)){
        return false;
    }
    return true;
}

bool Lobby::ask_for_games(bool& is_close){
    std::list<std::unique_ptr<game_t>>& games = this->games_manager.get_games();
    int size = games.size();
    protocol.send_games_size(size);
    for (auto& game: games) {
        games_DTO game_dto;
        game_dto.game_id = game->game_id;
        game_dto.current_players = game->player_count;
        game_dto.max_players = game->max_players;
        protocol.send_games(game_dto);
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
    uint8_t key_code;
    bool is_close = false;
    key_code = protocol.receive_key_code();
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