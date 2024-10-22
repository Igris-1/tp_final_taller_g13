#include "server.h"

#define RDWR 2
#define QUEUE_MAX_SIZE 200
#define STOP_CODE "q"

Server::Server(const char* port): port(port) { run(); }

Server::~Server() {
    CommandInfo* command_info = nullptr;
    while (receiverQueue.try_pop(command_info) && command_info) {
        delete command_info;
    }
    delete clientHandlerQueues;
}

void Server::run() {
    try {
        clientHandlerQueues = new ThreadSafeList<ClientHandler>();
        Socket socket_server = Socket(port);
        AcceptorThread acceptor(socket_server, receiverQueue, clientHandlerQueues);
        GameThread gameThread(receiverQueue, clientHandlerQueues);

        std::string input;
        while (input != STOP_CODE) {
            std::getline(std::cin, input);
        }

        socket_server.shutdown(RDWR);
        socket_server.close();

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