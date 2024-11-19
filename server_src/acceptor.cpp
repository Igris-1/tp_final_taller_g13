
#include "acceptor.h"

#include <queue>
#include <utility>

#include "../common_src/action_t.h"
#include "../common_src/liberror.h"
#include "../common_src/socket.h"
#include "actions/duck_creator.h"
#include "../common_src/duck_DTO.h"

#include "client_handler.h"
#include "list_of_clients_monitor.h"
#include "protocol_server.h"
#include "games_manager.h"

#define SHUT_DOWN_TWO 2
#define NEW_GAME 0
#define JOIN_GAME 1

Acceptor::Acceptor(const char* port, GamesManager& gameManager):
        socket(port), games_manager(gameManager) {
        start();
}

void Acceptor::run() {
    try {
        // int idCount = 0;
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
            ss.recvall(&buffer, 1, &aux);
            std::cout << "acceptor recibio un: " << static_cast<int> (buffer) << std::endl;
            if(buffer == NEW_GAME){
                this->games_manager.create_new_game();
                std::cout << "acceptor creando nueva partida" << std::endl;
                uint8_t code2 = 0x05;
                ss.sendall(&code2, 1, &aux);
                ss.recvall(&buffer, 1, &aux);
                this->games_manager.add_client_to_game(this->games_manager.get_game_counter() - 1, std::move(ss), buffer);
                std::cout << "acceptor agregando cliente a partida" << std::endl;
            }else{  
                try{
                    //this->games_manager.create_new_game(static_cast<int> (buffer));
                    uint8_t code2 = 0x05;
                    ss.sendall(&code2, 1, &aux);
                    uint8_t buffer2;
                    ss.recvall(&buffer2, 1, &aux);

                    std::list<std::unique_ptr<game_t>>& games = this->games_manager.get_games();
                    int size = games.size();
                    uint8_t code = 0x04;
                    ss.sendall(&code, 1, &aux);
                    ss.sendall(&size, 1, &aux);
                    for(auto& game : games){
                        games_DTO game_dto;
                        game_dto.game_id = game->game_id;
                        game_dto.current_players = game->player_count;
                        game_dto.max_players = 4;
                        ss.sendall(&game_dto, sizeof(games_DTO), &aux);
                    }
                    std::cout << "acceptor espera recibir algo" << std::endl;
                    ss.recvall(&buffer, 1, &aux);
                    std::cout << "acceptor recibio un: " << static_cast<int> (buffer) << std::endl;
                    this->games_manager.add_client_to_game(static_cast<int> (buffer), std::move(ss), buffer2);
                    std::cout << "acceptor agregando cliente a partida existente" << std::endl;
                }catch(const GamesManagerError& e){
                    ss.shutdown(SHUT_DOWN_TWO);
                    ss.close();
                    continue;
                }
            }

            //clients.addClient(std::move(ss), gameQueue, idCount);

            //std::shared_ptr<Action> create_duck = std::make_shared<DuckCreator>(idCount);
            //gameQueue.push(create_duck);
            //idCount = idCount + 2;
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
