#ifndef RECEIVER_THREAD_H_
#define RECEIVER_THREAD_H_

#include <iostream>
#include <string>
#include <vector>

#include <liberror.h>

#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "actions/action.h"
#include "actions/client_action_t.h"
#include "actions/duck_creator.h"
#include "actions/player_commands.h"

#include "protocol_server.h"

class ReceiverThread: public Thread {
private:
    Queue<std::shared_ptr<Action>>& queue;
    ProtocolServer& protocol;
    int clientId;

    void run() override {

        int number_of_players = protocol.receive_number_of_players();
        for (int i = 1; i < number_of_players; i++) {
            std::shared_ptr<Action> create_duck = std::make_shared<DuckCreator>(clientId + i);
            queue.push(create_duck);
        }

        while (!protocol.socket_closed() && _keep_running) {
            try {
                action_t action = protocol.receive_action();
                std::shared_ptr<Action> command =
                        std::make_shared<PlayerCommands>(clientId, action);
                queue.push(command);
            } catch (const std::exception& e) {
                std::cerr << "Exception while in receiver thread: " << e.what() << std::endl;
            }
        }
    }

public:
    ReceiverThread(Queue<std::shared_ptr<Action>>& queue, ProtocolServer& protocol, int id):
            queue(queue), protocol(protocol), clientId(id) {
        start();
    }

    ~ReceiverThread() override { _is_alive = false; }
};

#endif