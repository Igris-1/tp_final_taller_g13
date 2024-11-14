#include "list_of_clients_monitor.h"

#include <iostream>
#include <stdexcept>
#include <utility>

#include "../common_src/game_snapshot_t.h"
#include "../common_src/liberror.h"
#include "../common_src/socket.h"
#include "actions/action.h"

ListOfClientsMonitor::ListOfClientsMonitor() {}

void ListOfClientsMonitor::addClient(Socket&& client, Queue<std::shared_ptr<Action>>& gameQueue,
                                     int idCount) {
    std::lock_guard<std::mutex> lock(mutex);
    Queue<game_snapshot_t> senderQueue;
    this->clientsList.emplace_back(std::move(client), gameQueue, idCount);
}
// cppcheck-suppress passedByValue
void ListOfClientsMonitor::enqueue_snapshot(game_snapshot_t command) {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto it = clientsList.begin(); it != clientsList.end();) {
        if (it->is_alive()) {
            it->push(command);
            ++it;
        } else {
            it = clientsList.erase(it);
        }
    }
}

void ListOfClientsMonitor::send_map(map_structure_t map) {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto it = clientsList.begin(); it != clientsList.end();) {
        if (it->is_alive()) {
            it->send_map(map);
            ++it;
        } else {
            it = clientsList.erase(it);
        }
    }
}

ListOfClientsMonitor::~ListOfClientsMonitor() {}
