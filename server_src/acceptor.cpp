
#include "acceptor.h"

#include <cstdint>
#include <queue>
#include <utility>

#include "../common_src/action_t.h"
#include "../common_src/DTOs.h"
#include "../common_src/liberror.h"
#include "../common_src/socket.h"
#include "actions/duck_creator.h"

#include "client_handler.h"
#include "games_manager.h"
#include "list_of_clients_monitor.h"
#include "protocol_server.h"

#define SHUT_DOWN_TWO 2
#define NEW_GAME 0
#define JOIN_GAME 1
#define JOIN_TO_RANDOM_GAME 3
#define ASK_FOR_GAMES 2
Acceptor::Acceptor(const char* port, GamesManager& gameManager):
        socket(port), games_manager(gameManager) {
    start();
}

void Acceptor::run() {
    try {
        while (_keep_running) {
            Socket ss = socket.accept();
            /*recvall(que partida queres jugar? o una nueva)
            if(partida exite){
                clients.addClient(std::move(ss), gameQueue, idCount, idPartida);}
                else{
                crear partida y agregar
            */
            uint8_t buffer;
            bool aux;
            ss.recvall(&buffer, ONE_BYTE, &aux);
            if (buffer == NEW_GAME) {
                this->games_manager.create_new_game();
                uint8_t code2 = 0x05;
                ss.sendall(&code2, ONE_BYTE, &aux);
                ss.recvall(&buffer, ONE_BYTE, &aux);
                this->games_manager.add_client_to_game(this->games_manager.get_game_counter(),
                                                       std::move(ss), buffer);

            } else if (buffer == JOIN_TO_RANDOM_GAME) {
                try {
                    uint8_t code2 = 0x05;
                    ss.sendall(&code2, ONE_BYTE, &aux);
                    uint8_t buffer2;
                    ss.recvall(&buffer2, ONE_BYTE, &aux);
                    this->games_manager.add_client_to_random_game(std::move(ss), buffer2);
                } catch (const GamesManagerError& e) {
                    ss.shutdown(SHUT_DOWN_TWO);
                    ss.close();
                    continue;
                }
            } else if (buffer == JOIN_GAME) {
                uint8_t code = 0x06;
                ss.sendall(&code, ONE_BYTE, &aux);

                uint8_t buffer;
                ss.recvall(&buffer, ONE_BYTE, &aux);
                uint8_t buffer2;
                ss.recvall(&buffer2, ONE_BYTE, &aux);

                this->games_manager.add_client_to_game(buffer2, std::move(ss), buffer);

            } else if (buffer == ASK_FOR_GAMES) {
                std::list<std::unique_ptr<game_t>>& games = this->games_manager.get_games();
                uint16_t size = games.size();
                uint8_t code = 0x04;
                ss.sendall(&code, ONE_BYTE, &aux);
                ss.sendall(&size, TWO_BYTES, &aux);
                for (auto& game: games) {
                    games_DTO game_dto;
                    game_dto.game_id = game->game_id;
                    game_dto.current_players = game->player_count;
                    game_dto.max_players = 4;
                    TranslatorDTOs translator_games;
                    translator_games.hton_games_DTO(&game_dto);
                    ss.sendall(&game_dto, sizeof(games_DTO), &aux);
                }
            }
        }
    } catch (const LibError& e) {
        stop();
    }
}

void Acceptor::close() {
    socket.shutdown(SHUT_DOWN_TWO);
    socket.close();
}

Acceptor::~Acceptor() {}