#ifndef SENDER_H
#define SENDER_H

#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include <SDL2/SDL.h>
#include <iostream>

#include "protocol_client.h"
#include <unistd.h>

class Sender: public Thread {
private:
    ProtocolClient& protocol;

    void run() override {
        try {
            bool quit = false;
            SDL_Event e;
            while (!quit && !protocol.socket_closed() && _keep_running) {
                if (SDL_PollEvent(&e)!=0){
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {
                        action_t action;
                        switch (e.key.keysym.sym) {
                            case SDLK_a:
                                action.left = true;
                                protocol.send_action(action);
                                break;
                            case SDLK_d:
                                action.right = true;
                                protocol.send_action(action);
                                break;
                            default:
                                break;
                        }
                    }
                }
            }   
        } catch (const ClosedQueue& e) {
            stop();
        } catch (const std::exception& e) {
            std::cerr << "Exception while in client sender thread: " << e.what() << std::endl;
        }
    }

public:
    Sender(ProtocolClient& protocol): protocol(protocol) {
        start();
    }

    ~Sender() override { 
        _is_alive = false;
    }
};

#endif  // SENDER_H
