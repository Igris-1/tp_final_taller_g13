#include "client_handler.h"
#include <utility>
#include "action.h"
#define QUEUE_MAX_SIZE 200

ClientHandler::ClientHandler(Socket&& socket, Queue<std::shared_ptr<Action>>& gameQueue, int id):
        protocol(std::move(socket)),
        senderQueue(QUEUE_MAX_SIZE),
        senderThread(senderQueue, protocol),
        receiverThread(gameQueue, protocol, id),
        clientID(id) {}
void ClientHandler::push(game_snapshot_t gs) {
    try {
        if (is_alive()) {
            senderQueue.push(gs);
        }
    } catch (const ClosedQueue& e) {

        if (is_alive()) {
            std::cerr << "Closed sender queue in client handler" << e.what()
                      << std::endl;
        }
    }
}

bool ClientHandler::is_alive() { return senderThread.is_alive() && receiverThread.is_alive(); }

ClientHandler::~ClientHandler() {
    game_snapshot_t* gs;

    protocol.shutDown();

    senderQueue.close();

    senderThread.stop();
    receiverThread.stop();
    senderThread.join();
    receiverThread.join();
}
