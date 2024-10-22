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
    Queue<GameSnapshot*>& queue;
    Protocol& protocol;

    void run() override {

        while (_keep_running) {
            try {
                GameSnapshot* gs = queue.pop();

                protocol.send_game_snapshot(*gs);

                delete gs;

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
    SenderThread(Queue<GameSnapshot*>& queue, Protocol& protocol): queue(queue), protocol(protocol) {
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