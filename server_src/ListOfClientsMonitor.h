//
// Created by pedro on 10/1/24.
//

#ifndef LISTOFCLIENTSMONITOR_H
#define LISTOFCLIENTSMONITOR_H
#include <list>
#include <mutex>
#include "../common_src/queue.h"

#include "client_handler.h"


class ListOfClientsMonitor {

private:
    //  cppcheck-suppress unusedStructMember
    std::mutex mutex;
    //  cppcheck-suppress unusedStructMember
    std::list<ClientHandler> clientsList;

public:
    ListOfClientsMonitor();

    void addClient(Socket&& client, Queue<action_t>& gameQueue);

    void enqueueCommand(game_snapshot_t command);

    ~ListOfClientsMonitor();
};


#endif  // LISTOFCLIENTSMONITOR_H
