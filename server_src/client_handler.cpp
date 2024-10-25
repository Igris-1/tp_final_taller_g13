#include "client_handler.h"

#include <utility>

#define QUEUE_MAX_SIZE 200

ClientHandler::ClientHandler(Socket&& socket, Queue<action_t>& gameQueue):
        protocol(std::move(socket)),
        senderQueue(QUEUE_MAX_SIZE),
        senderThread(senderQueue, protocol),
        gameThread(gameQueue, protocol) {}

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
    }
}

bool ClientHandler::is_alive() { return senderThread.is_alive() && gameThread.is_alive(); }

ClientHandler::~ClientHandler() {

    game_snapshot_t* gs;

    protocol.shutDown();

    senderQueue.close();

    senderThread.stop();
    gameThread.stop();

    senderThread.join();

    gameThread.join();
}