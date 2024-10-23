
#include "Acceptor.h"

#include <queue>
#include <utility>

#include "../common_src/liberror.h"
#include "../common_src/socket.h"

#include "client_handler.h"
#include "ListOfClientsMonitor.h"
#include "ProtocolServer.h"

#define SHUT_DOWN_TWO 2

Acceptor::Acceptor(const char* port, Queue<action_t>& gameQueue, ListOfClientsMonitor* clients): socket(port), gameQueue(gameQueue), clients(clients){
    start();
}

void Acceptor::run(){
    try {
        while (true) {
            Socket ss = socket.accept();
            clients->addClient(std::move(ss), gameQueue);
        }
    } catch (const LibError& e) {
        return;
    }
}

void Acceptor::close() {
    socket.shutdown(SHUT_DOWN_TWO);
    socket.close();
}

Acceptor::~Acceptor() {}
