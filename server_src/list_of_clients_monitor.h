#ifndef LISTOFCLIENTSMONITOR_H
#define LISTOFCLIENTSMONITOR_H
#include <list>
#include <mutex>

#include "../common_src/queue.h"
#include "actions/action.h"

#include "client_handler.h"


class ListOfClientsMonitor {

private:
    //  cppcheck-suppress unusedStructMember
    std::mutex mutex;
    //  cppcheck-suppress unusedStructMember
    std::list<ClientHandler> clientsList;

public:
    ListOfClientsMonitor();

    void addClient(Socket&& client, Queue<std::shared_ptr<Action>>& gameQueue, int idCount);

    void enqueue_snapshot(game_snapshot_t command);

    void enqueue_instruction(instruction_for_client_t command);

    void enqueue_score(score_DTO score);

    void send_map(map_structure_t map);

    ~ListOfClientsMonitor();
};


#endif  // LISTOFCLIENTSMONITOR_H
