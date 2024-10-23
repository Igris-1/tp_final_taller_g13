#include "server.h"
#include "Acceptor.h"

#define RDWR 2
#define QUEUE_MAX_SIZE 200
#define STOP_CODE "q"

Server::Server(const char* port) {
    this->port = port;
}

Server::~Server() {
}

void Server::start() {
    try {

        Queue<action_t> gameQueue = Queue<action_t>(QUEUE_MAX_SIZE);
        ListOfClientsMonitor clients;

        Acceptor acceptor(port, gameQueue, &clients);
        //GameThread gameThread(gameQueue, clients); lo comentopq por ahora no quier usar esto

        std::string input;
        while (input != STOP_CODE) {
            std::getline(std::cin, input);
        }
        acceptor.close();    
        acceptor.stop();
        acceptor.join();
        //gameThread.stop(); comentado pq no lo uso todavia
        //gameThread.join();

    } catch (const std::bad_alloc& e) {
        std::cerr << "No se pudo allocar memoria en el server: " << e.what() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Hubo una excepción en el server: " << e.what() << std::endl;
    }
}