//
// Created by pedro on 10/13/24.
//

#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "ListOfClientsMonitor.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "../common_src/socket.h"


class Acceptor: public Thread{

private:
    Socket socket;
    Queue<action_t>& gameQueue;
    ListOfClientsMonitor* clients;
    void run() override;

public:
    explicit Acceptor(const char* port, Queue<action_t>& gameQueue, ListOfClientsMonitor* clients);
    void close();
    ~Acceptor();
};


#endif  // ACCEPTOR_H
