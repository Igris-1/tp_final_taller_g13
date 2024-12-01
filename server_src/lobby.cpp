#include "lobby.h"

#define SHUT_DOWN_TWO 2
#define NEW_GAME 0
#define JOIN_GAME 1
#define JOIN_TO_RANDOM_GAME 3
#define ASK_FOR_GAMES 2

Lobby::Lobby(GamesManager& games_manager, Socket&& socket)
    : games_manager(games_manager),
      socket(std::move(socket)) {
        start();
      }

void Lobby::run() {
try {
    std::cout << "Lobby running" << std::endl;  
    uint8_t buffer;
    bool aux;
    socket.recvall(&buffer, ONE_BYTE, &aux);
    if (buffer == NEW_GAME) {
        std::cout << "Creating new game" << std::endl;
        this->games_manager.create_new_game();
        uint8_t code2 = 0x05;
        socket.sendall(&code2, ONE_BYTE, &aux);
        socket.recvall(&buffer, ONE_BYTE, &aux);
        std::cout << "Adding client to game" << std::endl;
        this->games_manager.add_client_to_game(this->games_manager.get_game_counter(),
                                                std::move(socket), buffer);
        std::cout << "Client added to game" << std::endl;

    } else if (buffer == JOIN_TO_RANDOM_GAME) {
        try {
            uint8_t code2 = 0x05;
            socket.sendall(&code2, ONE_BYTE, &aux);
            uint8_t buffer2;
            socket.recvall(&buffer2, ONE_BYTE, &aux);
            this->games_manager.add_client_to_random_game(std::move(socket), buffer2);
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

        this->games_manager.add_client_to_game(buffer2, std::move(socket), buffer);

    } else if (buffer == ASK_FOR_GAMES) {
        std::list<std::unique_ptr<game_t>>& games = this->games_manager.get_games();
        uint16_t size = games.size();
        uint8_t code = 0x04;
        socket.sendall(&code, ONE_BYTE, &aux);
        socket.sendall(&size, TWO_BYTES, &aux);
        for (auto& game: games) {
            games_DTO game_dto;
            game_dto.game_id = game->game_id;
            game_dto.current_players = game->player_count;
            game_dto.max_players = 4;
            TranslatorDTOs translator_games;
            translator_games.hton_games_DTO(&game_dto);
            socket.sendall(&game_dto, sizeof(games_DTO), &aux);
        }
    }
    stop();
    std::cout << "Lobby finished" << std::endl;
 }catch (const LibError& e) {
       stop();
    }
}



Lobby::~Lobby() {}