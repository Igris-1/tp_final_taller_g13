#include "server.h"

#include "actions/action.h"
#include "games_manager.h"

#include "acceptor.h"

#define RDWR 2
#define QUEUE_MAX_SIZE 200
#define STOP_CODE "q"

Server::Server(const char* port): port(port) {}

Server::~Server() {}



void Server::start() {
    try {
        GamesManager gamesManager;
        Acceptor acceptor(port, gamesManager);
        std::string input;
        while (input != STOP_CODE) {
            std::getline(std::cin, input);
        }
        acceptor.close();
        acceptor.stop();
        acceptor.join();

    } catch (const std::bad_alloc& e) {
        std::cerr << "No se pudo allocar memoria en el server: " << e.what() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Hubo una excepción en el server: " << e.what() << std::endl;
    }
}