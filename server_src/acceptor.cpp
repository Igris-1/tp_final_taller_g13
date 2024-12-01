
#include "acceptor.h"

#include <cstdint>
#include <unistd.h>
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
#include "lobby.h"

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
            std::cout << "New connection" << std::endl;
            this->lobbies.emplace_back(games_manager, std::move(ss));
            for (Lobby& lobby : lobbies) {
                if (!lobby.is_alive()) {
                    std::cout << "Lobby joined" << std::endl;
                    lobby.join();
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
    for (Lobby& lobby : lobbies) {
        std::cout << "Lobby joined" << std::endl;
        lobby.stop();
        lobby.join();
    }
}

Acceptor::~Acceptor() {}