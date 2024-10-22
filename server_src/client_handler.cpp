#include "client_handler.h"

#include <utility>

#define QUEUE_MAX_SIZE 200

ClientHandler::ClientHandler(Socket&& socket, Queue<CommandInfo*>& receiverQueue):
        protocol(std::move(socket)),
        senderQueue(QUEUE_MAX_SIZE),
        senderThread(senderQueue, protocol),
        receiverThread(receiverQueue, protocol) {}

void ClientHandler::push(GameSnapshot* gs) {
    try {
        if (is_alive()) {
            senderQueue.push(gs);
        }
    } catch (const ClosedQueue& e) {

        if (is_alive()) {
            std::cerr << "Closed sneder queue in client handler" << e.what()
                      << std::endl;  // if client is alive, then it's a bug
        }
        delete gs;  // if the client is not alive, then acceptor should delete it in reap_dead
    }
}

bool ClientHandler::is_alive() { return senderThread.is_alive() && receiverThread.is_alive(); }

ClientHandler::~ClientHandler() {

    GameSnapshot* gs;
    while (senderQueue.try_pop(gs) && gs) {
        delete gs;
    }

    protocol.kill_socket();

    senderQueue.close();

    senderThread.stop();
    receiverThread.stop();

    senderThread.join();

    receiverThread.join();
}