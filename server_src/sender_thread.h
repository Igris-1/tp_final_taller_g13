#ifndef SENDER_THREAD_H_
#define SENDER_THREAD_H_

#include <iostream>
#include <string>
#include <variant>

#include "../common_src/protocol.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"


class SenderThread: public Thread {
private:
    Queue<game_snapshot_t>& queue;
    ProtocolServer& protocol;

    void run() override {
        bool was_closed = false;
        while (_keep_running && !was_closed) {
            try {
                game_snapshot_t gs = queue.pop();

                protocol.sendGameInfo(gs, &was_closed);

                //delete gs; ya no, gs es un struct simple

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
        try {
            start();
        } catch (const std::exception& e) {
            std::cerr << "Failed to start sendert hread: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Unknown error occurred while starting sender thread." << std::endl;
        }
    }

    ~SenderThread() override { _is_alive = false; }
};

#endif