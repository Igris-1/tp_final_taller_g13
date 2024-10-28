#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "list_of_clients_monitor.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "../common_src/socket.h"
#include "client_action_t.h"


class Acceptor: public Thread{

private:
    Socket socket;
    Queue<client_action_t>& gameQueue;
    ListOfClientsMonitor& clients;
    void run() override;

public:
    explicit Acceptor(const char* port, Queue<client_action_t>& gameQueue, ListOfClientsMonitor& clients);
    void close();
    ~Acceptor();
};


#endif  // ACCEPTOR_H
