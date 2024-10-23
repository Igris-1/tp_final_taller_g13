//
// Created by pedro on 10/1/24.
//

#include "ListOfClientsMonitor.h"

#include <iostream>
#include <stdexcept>
#include <utility>

#include "../common_src/liberror.h"
#include "../common_src/socket.h"

ListOfClientsMonitor::ListOfClientsMonitor() {}

void ListOfClientsMonitor::addClient(Socket&& client,
                                     Queue<action_t>& gameQueue) {
    std::lock_guard<std::mutex> lock(mutex);
    Queue<game_snapshot_t> senderQueue;
    this->clientsList.emplace_back(std::move(client), gameQueue);
}
// cppcheck-suppress passedByValue
void ListOfClientsMonitor::enqueueCommand(game_snapshot_t command) {
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
