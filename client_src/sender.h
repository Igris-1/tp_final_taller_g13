#ifndef SENDER_H
#define SENDER_H

#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "protocol_client.h"

class Sender: public Thread {
private:
    ProtocolClient& protocol;
    Queue<action_t>& queue;

    void run() override {
        while (!protocol.socket_closed() && _keep_running) {
            try {
                // implementar
                action_t action = queue.pop();
                protocol.send_action(action);
            } catch (const std::exception& e) {
                std::cerr << "Exception while in client sender thread: " << e.what() << std::endl;
            }
        }
    }

public:
    Sender(ProtocolClient& protocol, Queue<action_t>& queue): protocol(protocol), queue(queue) {
        start();
    }

    ~Sender() override { _is_alive = false; }
};

#endif  // SENDER_H
