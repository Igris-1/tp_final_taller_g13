#ifndef RECEIVER_THREAD_H_
#define RECEIVER_THREAD_H_

#include <iostream>
#include <string>
#include <vector>
#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "protocol_server.h"

class ReceiverThread: public Thread {
private:
    Queue<action_t>& queue;
    ProtocolServer& protocol;

    void run() override {
        while (!protocol.socket_closed() && _keep_running) {
            try {
                action_t action = protocol.receive_action();
                queue.push(action);
            } catch (const std::exception& e) {
                std::cerr << "Exception while in receiver thread: " << e.what() << std::endl;
            }
        }
    }

public:
    ReceiverThread(Queue<action_t>& queue, ProtocolServer& protocol):
            queue(queue), protocol(protocol) {
        start();
    }

    ~ReceiverThread() override { 
        _is_alive = false;
        }
};

#endif