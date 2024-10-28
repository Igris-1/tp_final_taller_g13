
#include "acceptor.h"

#include <queue>
#include <utility>

#include "../common_src/liberror.h"
#include "../common_src/socket.h"

#include "client_handler.h"
#include "list_of_clients_monitor.h"
#include "protocol_server.h"

#define SHUT_DOWN_TWO 2

Acceptor::Acceptor(const char* port, Queue<client_action_t>& gameQueue, ListOfClientsMonitor& clients): socket(port), gameQueue(gameQueue), clients(clients){
    start();
}

void Acceptor::run(){
    try {
        int idCount = 0;
        while (_keep_running) {
            Socket ss = socket.accept();
            clients.addClient(std::move(ss), gameQueue, idCount);
            idCount++;
        }
    } catch (const LibError& e) {
        stop();
    }
}

void Acceptor::close() {
    socket.shutdown(SHUT_DOWN_TWO);
    socket.close();
}

Acceptor::~Acceptor() {}
