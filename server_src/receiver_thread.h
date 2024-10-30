#ifndef RECEIVER_THREAD_H_
#define RECEIVER_THREAD_H_

#include <iostream>
#include <string>
#include <vector>
#include "action.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "protocol_server.h"
#include "client_action_t.h"
#include "player_commands.h"

class ReceiverThread: public Thread {
private:
    Queue<std::shared_ptr<Action>>& queue;
    ProtocolServer& protocol;
    int clientId;

    void run() override {
        while (!protocol.socket_closed() && _keep_running) {
            try {
                action_t action = protocol.receive_action();
                std::shared_ptr<Action> command = std::make_shared<PlayerCommands>(clientId, action);
                queue.push2(command);
            } catch (const std::exception& e) {
                std::cerr << "Exception while in receiver thread: " << e.what() << std::endl;
            }
        }
    }

public:
    ReceiverThread(Queue<std::shared_ptr<Action>>& queue, ProtocolServer& protocol, int id):
            queue(queue), protocol(protocol) {
        start();
    }

    ~ReceiverThread() override { 
        _is_alive = false;
        }
};

#endif