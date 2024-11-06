#include "server.h"
#include "acceptor.h"
#include "action.h"

#define RDWR 2
#define QUEUE_MAX_SIZE 200
#define STOP_CODE "q"
#define START_CODE "f"

Server::Server(const char* port) 
        : port(port) {
    start();
}

Server::~Server() {
}

void Server::start() {
    try {

        Queue<std::shared_ptr<Action>> gameQueue = Queue<std::shared_ptr<Action>>(QUEUE_MAX_SIZE);
        ListOfClientsMonitor clients;
        Acceptor acceptor(port, gameQueue, clients);
        std::string input;
        while (input != START_CODE) {
            std::getline(std::cin, input);
        }

        GameThread gameThread(gameQueue, clients);
        while (input != STOP_CODE) {
            std::getline(std::cin, input);
        }
        acceptor.close();    
        acceptor.stop();
        acceptor.join();
        gameThread.stop();
        gameThread.join();

    } catch (const std::bad_alloc& e) {
        std::cerr << "No se pudo allocar memoria en el server: " << e.what() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Hubo una excepción en el server: " << e.what() << std::endl;
    }
}