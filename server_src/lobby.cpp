#include "lobby.h"

#define SHUT_DOWN_TWO 2
#define NEW_GAME 0
#define JOIN_GAME 1
#define JOIN_TO_RANDOM_GAME 3
#define ASK_FOR_GAMES 2
#define PRACTICE_GAME 4

Lobby::Lobby(GamesManager& games_manager, Socket&& socket)
    : games_manager(games_manager),
      socket(std::move(socket)) {
        std::cout << "Lobby start" << std::endl;
        start();
        std::cout << "Lobby started" << std::endl;
      }

void Lobby::run() {
try {
    std::cout << "Lobby running" << std::endl;  
    uint8_t buffer;
    bool aux = true;
    socket.recvall(&buffer, ONE_BYTE, &aux);
    if (buffer == NEW_GAME) {
        std::cout << "Creating new game" << std::endl;
        
        uint8_t code2 = 0x05;
        socket.sendall(&code2, ONE_BYTE, &aux);
        socket.recvall(&buffer, ONE_BYTE, &aux);
        uint8_t code = 0x08;
        uint8_t  maxplayers;
        socket.sendall(&code, ONE_BYTE, &aux);
        socket.recvall(&maxplayers, ONE_BYTE, &aux);
        std::cout << "Max players: " << (int)maxplayers << std::endl;
        std::cout << "Adding client to game" << std::endl;
        if(!this->games_manager.create_new_game(std::move(socket), buffer, (int)maxplayers)){
            std::cout << "Error creating game" << std::endl;
        }
        std::cout << "Client added to game" << std::endl;

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
                // uint8_t code2 = 0x07;
                // socket.sendall(&code, ONE_BYTE, &aux);
        }
    } else if (buffer == ASK_FOR_GAMES) {
        std::list<std::unique_ptr<game_t>>& games = this->games_manager.get_games();
        uint16_t size = games.size();
        uint8_t code = 0x04;
        socket.sendall(&code, ONE_BYTE, &aux);
        socket.sendall(&size, TWO_BYTES, &aux);
        for (auto& game: games) {
            games_DTO game_dto;
            game_dto.game_id = game->game_id;
            std::cout << "Game id: " << game->game_id << std::endl;
            game_dto.current_players = game->player_count;
            std::cout << "Current players: " << game->player_count << std::endl;
            game_dto.max_players = 4;
            TranslatorDTOs translator_games;
            translator_games.hton_games_DTO(&game_dto);
            socket.sendall(&game_dto, sizeof(games_DTO), &aux);
        }
    } else if(buffer == PRACTICE_GAME){
        this->games_manager.add_to_practice_game(std::move(socket));
    }
    std::cout << "Lobby finished" << std::endl;
 }catch (const LibError& e) {
    }
}

Lobby::~Lobby() {}