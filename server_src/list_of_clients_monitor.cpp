#include "list_of_clients_monitor.h"

#include <iostream>
#include <stdexcept>
#include <utility>

#include "../common_src/liberror.h"
#include "../common_src/socket.h"
#include "../common_src/game_snapshot_t.h"

ListOfClientsMonitor::ListOfClientsMonitor() {}

void ListOfClientsMonitor::addClient(Socket&& client,
                                     Queue<client_action_t>& gameQueue, int idCount) {
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

ListOfClientsMonitor::~ListOfClientsMonitor() {}