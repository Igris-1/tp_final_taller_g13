#include "lobby.h"

#include <filesystem>
#include <string>

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
      socket(std::move(socket)) {
        std::cout << "Lobby start" << std::endl;
        start();
        std::cout << "Lobby started" << std::endl;
      }

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
    std::cout << "Max players: " << (int)maxplayers << std::endl;
    std::cout << "Adding client to game" << std::endl;
    if(!custom_map){
        if(!this->games_manager.create_new_game(std::move(socket), buffer, (int)maxplayers)){
            std::cout << "Error creating game" << std::endl;
        }
        std::cout << "Client added to game" << std::endl;
        return;
    }

    std::string map_name;
    code = 0x09;
    this->socket.sendall(&code, ONE_BYTE, &aux);

    this->socket.recvall(&buffer, ONE_BYTE, &aux);

    char namebuffer [buffer+1];
    this->socket.recvall(&namebuffer, buffer, &aux);
    namebuffer[buffer] = '\0';
    map_name = std::string(namebuffer);
    this->games_manager.create_new_custom_game(std::move(socket), buffer, (int)maxplayers, map_name);
}

void Lobby::run() {
try {
    std::cout << "Lobby running" << std::endl;  
    uint8_t buffer = 0;
    bool aux = true;
    socket.recvall(&buffer, ONE_BYTE, &aux);
    std::cout << "Buffer: " << (int)buffer << std::endl;
    if (buffer == NEW_GAME) {
        std::cout << "Creating new game" << std::endl;
        
        creating_game(false);

    } else if (buffer == JOIN_TO_RANDOM_GAME) {
        try {
            uint8_t code2 = 0x05;
            socket.sendall(&code2, ONE_BYTE, &aux);
            uint8_t buffer2;
            socket.recvall(&buffer2, ONE_BYTE, &aux);
            if(!this->games_manager.add_client_to_random_game(std::move(socket), buffer2)){
                std::cout << "Error joining game" << std::endl;
            }
        } catch (const GamesManagerError& e) {
            socket.shutdown(SHUT_DOWN_TWO);
            socket.close();
            return;
        }
    } else if (buffer == JOIN_GAME) {
        uint8_t code = 0x06;
        socket.sendall(&code, ONE_BYTE, &aux);

        uint8_t buffer;
        socket.recvall(&buffer, ONE_BYTE, &aux);
        uint8_t buffer2;
        socket.recvall(&buffer2, ONE_BYTE, &aux);
        if(!this->games_manager.add_client_to_game(buffer2, std::move(socket), buffer)){
            std::cout << "Error joining game" << std::endl;
        }
    } else if (buffer == ASK_FOR_GAMES) {
        std::list<std::unique_ptr<game_t>>& games = this->games_manager.get_games();
        uint16_t size = games.size();
        uint8_t code = 0x04;
        socket.sendall(&code, ONE_BYTE, &aux);
        size = htons(size);
        socket.sendall(&size, TWO_BYTES, &aux);
        for (auto& game: games) {
            games_DTO game_dto;
            game_dto.game_id = game->game_id;
            std::cout << "Game id: " << game->game_id << std::endl;
            game_dto.current_players = game->player_count;
            std::cout << "Current players: " << game->player_count << std::endl;
            game_dto.max_players = game->max_players;
            TranslatorDTOs translator_games;
            translator_games.hton_games_DTO(&game_dto);
            socket.sendall(&game_dto, sizeof(games_DTO), &aux);
        }
    } else if(buffer == PRACTICE_GAME){
        this->games_manager.add_to_practice_game(std::move(socket));
    } else if(buffer == ASK_FOR_MAPS){
        std::cout << "Asking for maps" << std::endl;
        const fs::path directory_path = "../maps";
        try {
            if (fs::exists(directory_path) && fs::is_directory(directory_path)) {
                for (const auto& entry : fs::directory_iterator(directory_path)) {
                    std::string relative_path = entry.path().filename().string();
                    
                    size_t stop_pos = relative_path.find('.');
                    if (stop_pos != std::string::npos) {
                        relative_path = relative_path.substr(0, stop_pos);
                    }
                    
                    std::cout << "Relative path: " << relative_path << '\n';
                    
                    uint8_t size = relative_path.size();
                    socket.sendall(&size, ONE_BYTE, &aux);
                    socket.sendall(relative_path.c_str(), size, &aux);
                }
                uint8_t zero = 0;
                socket.sendall(&zero, ONE_BYTE, &aux);
            } else {
                std::cerr << "Path does not exist or is not a directory.\n";
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Filesystem error: " << e.what() << '\n';
        }
    }else if(buffer == NEW_GAME_CUSTOM){
        creating_game(true);
    }
    std::cout << "Lobby finished" << std::endl;
 }catch (const LibError& e) {
    }
}

Lobby::~Lobby() {}