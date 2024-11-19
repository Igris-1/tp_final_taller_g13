#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "../common_src/action_t.h"
#include "../common_src/queue.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"
#include "actions/action.h"
#include "actions/client_action_t.h"
#include "games_manager.h"
#include "list_of_clients_monitor.h"


class Acceptor: public Thread {

private:
    Socket socket;
    GamesManager& games_manager;
    void run() override;

public:
    explicit Acceptor(const char* port, GamesManager& gameManager);
    void close();
    ~Acceptor();
};


#endif  // ACCEPTOR_H
