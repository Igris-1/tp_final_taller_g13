#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "list_of_clients_monitor.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "../common_src/socket.h"
#include "actions/client_action_t.h"
#include "../common_src/action_t.h"
#include "actions/action.h"


class Acceptor: public Thread{

private:
    Socket socket;
    Queue<std::shared_ptr<Action>>& gameQueue;
    ListOfClientsMonitor& clients;
    void run() override;

public:
    explicit Acceptor(const char* port, Queue<std::shared_ptr<Action>>& gameQueue, ListOfClientsMonitor& clients);
    void close();
    ~Acceptor();
};


#endif  // ACCEPTOR_H
