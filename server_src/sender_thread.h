#ifndef SENDER_THREAD_H_
#define SENDER_THREAD_H_

#include <iostream>
#include <string>
#include <variant>

#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "../common_src/game_snapshot_t.h"


class SenderThread: public Thread {
private:
    Queue<game_snapshot_t>& queue;
    ProtocolServer& protocol;

    void run() override {
        while (!protocol.socket_closed() && _keep_running){
            try {

                game_snapshot_t gs = queue.pop();
                protocol.sendGameInfo(gs);
 
            } catch (const ClosedQueue& e) {
                stop();
            } catch (const std::exception& e) {
                std::cerr << "Exception while in sender thread: " << e.what() << std::endl;
            } catch (...) {
                std::cerr << "Unknown exception caught in sender thread." << std::endl;
            }
        }
    }

public:
    SenderThread(Queue<game_snapshot_t>& queue, ProtocolServer& protocol): queue(queue), protocol(protocol) {
        start();
    }

    ~SenderThread() override { 
        _is_alive = false; 
    }
};

#endif