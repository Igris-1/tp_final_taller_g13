#ifndef RECEIVER_THREAD_H_
#define RECEIVER_THREAD_H_

#include <iostream>
#include <string>
#include <vector>

#include "../common_src/protocol.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

class ReceiverThread: public Thread {
private:
    Queue<action_t>& queue;
    ProtocolServer& protocol;

    void run() override {
        bool was_closed = false;
        while (!was_closed && _keep_running) {
            try {
                /*CommandInfo* command_info = protocol.read_command();
                queue.push(command_info);*/
                action_t action = protocol.receiveDataFromClient(&was_closed);
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

    ~ReceiverThread() override { _is_alive = false; }
};

#endif