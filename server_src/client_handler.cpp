#include "client_handler.h"

#include <utility>

#define QUEUE_MAX_SIZE 200

ClientHandler::ClientHandler(Socket&& socket, Queue<action_t>& gameQueue):
        protocol(std::move(socket)),
        senderQueue(QUEUE_MAX_SIZE),
        senderThread(senderQueue, protocol),
        receiverThread(gameQueue, protocol) {}

void ClientHandler::push(game_snapshot_t gs) {
    try {
        if (is_alive()) {
            senderQueue.push(gs);
        }
    } catch (const ClosedQueue& e) {

        if (is_alive()) {
            std::cerr << "Closed sneder queue in client handler" << e.what()
                      << std::endl;
        }
        //delete gs;  // 
    }
}

bool ClientHandler::is_alive() { return senderThread.is_alive() && receiverThread.is_alive(); }

ClientHandler::~ClientHandler() {

    game_snapshot_t* gs;
    /*while (senderQueue.try_pop(gs) && gs) {
        delete gs;
    }*/ // no es necesario pq game snapshot no es un struct simplon

    protocol.shutDown();

    senderQueue.close();

    senderThread.stop();
    receiverThread.stop();

    senderThread.join();

    receiverThread.join();
}