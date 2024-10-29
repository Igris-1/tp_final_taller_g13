#ifndef RECEIVER_H
#define RECEIVER_H

#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "protocol_client.h"

class Receiver: public Thread {
private:
    ProtocolClient& protocol;
    Queue<action_t>& queue;

    void run() override {
        while (!protocol.socket_closed() && _keep_running) {
            try {
                // implementar
                // el receive
            } catch (const std::exception& e) {
                std::cerr << "Exception while in client receiver thread: " << e.what() << std::endl;
            }
        }
    }

public:
    Receiver(ProtocolClient& protocol, Queue<action_t>& queue): protocol(protocol), queue(queue) {
        start();
    }

    ~Receiver() override { _is_alive = false; }
};

#endif  // RECEIVER_H
