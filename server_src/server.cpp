#include "server.h"
#include "../common_src/socket.h"

#define RDWR 2
#define QUEUE_MAX_SIZE 200
#define STOP_CODE "q"

Server::Server(const char* port): port(port) { run(); }


void Server::run() {

    Socket socket_server = Socket(port);
    Socket socket = socket_server.accept();
    
    std::string input;
    while (input != STOP_CODE) {
        std::getline(std::cin, input);
    }

    return;

}
