#ifndef RECEIVER_H
#define RECEIVER_H

#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "protocol_client.h"
#include <SDL2/SDL.h>
#include <unistd.h>
#define SLEEP_TIME 200000

class Receiver: public Thread {
private:
    ProtocolClient& protocol;
    //Queue<game_snapshot_t>& queue;

    void run() override {
        while (!protocol.socket_closed() && _keep_running) {
            try {
                game_snapshot_t gs = protocol.read_snapshot();
                int x = static_cast<int>(gs.ducks[0].x);
                int y = static_cast<int>(gs.ducks[0].y);
                
                int len = gs.ducks.size();
                for (int i = 0; i < len; i++) {
                    int x = static_cast<int>(gs.ducks[i].x);
                    int y = static_cast<int>(gs.ducks[i].y);
                    std::cout << "Duck " << i << " at (" << x << ", " << y << ")" << std::endl;
                }

                usleep(SLEEP_TIME);
            } catch (const std::exception& e) {
                std::cerr << "Exception while in client receiver thread: " << e.what() << std::endl;
            }
        }
    }

public:
    Receiver(ProtocolClient& protocol): protocol(protocol) {
        start();
    }

    ~Receiver() override { _is_alive = false; }
};

#endif  // RECEIVER_H
