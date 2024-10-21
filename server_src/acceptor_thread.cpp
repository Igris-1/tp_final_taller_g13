#include "acceptor_thread.h"


AcceptorThread::AcceptorThread(Socket& socket, Queue<CommandInfo*>& receiverQueue,
                               ThreadSafeList<ClientHandler>* clientHandlerQueues):
        socket_server(socket),
        receiverQueue(receiverQueue),
        clientHandlerQueues(clientHandlerQueues) {
    start();
}

void AcceptorThread::reap_dead() {
    std::vector<ClientHandler*> toRemove;

    clientHandlerQueues->for_each([&toRemove](ClientHandler& clientHandler) {
        if (!clientHandler.is_alive()) {
            toRemove.push_back(&clientHandler);
        }
    });

    for (ClientHandler* clientHandler: toRemove) {
        clientHandlerQueues->remove(clientHandler);
    }
}

void AcceptorThread::kill_clients() {
    std::vector<ClientHandler*> toRemove;

    clientHandlerQueues->for_each(
            [&toRemove](ClientHandler& clientHandler) { toRemove.push_back(&clientHandler); });

    for (ClientHandler* clientHandler: toRemove) {
        clientHandlerQueues->remove(clientHandler);
    }
}

void AcceptorThread::run() {
    while (_keep_running) {
        try {

            Socket socket = socket_server.accept();
            ClientHandler* clientHandler = new ClientHandler(std::move(socket), receiverQueue);

            clientHandlerQueues->push_back(
                    clientHandler);  // I create pointers cause list couldnt compare them in find()
                                     // if i just moved them

            reap_dead();

        } catch (const LibError&) {
            stop();
            // If this error was thrown it means the server should be closed.
        } catch (...) {
            std::cerr << "Unknown exception caught." << std::endl;
        }
    }
}

AcceptorThread::~AcceptorThread() {
    kill_clients();
    _is_alive = false;
}