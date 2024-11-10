#ifndef SENDER_H
#define SENDER_H

#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include <SDL2/SDL.h>
#include <iostream>

#include "protocol_client.h"
#include <unistd.h>
#define SLEEP_TIME_SENDER 2000

class Sender: public Thread {
private:
    ProtocolClient& protocol;
    SDL_Event last_event;

    void run() override {
        try {
            bool quit = false;
            SDL_Event e;
            last_event.type = 0;

            while (!quit && !protocol.socket_closed() && _keep_running) {
                if (SDL_PollEvent(&e)!=0){
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else if (e.type == SDL_KEYUP) { // ES IMPORTANTE QUE EL EVENTO DE KEY_UP SE CHEQUE ANTES QUE EL DE KEY_DOWN
                        last_event = e;
                        action_t action;
                        switch (e.key.keysym.sym) {
                            case SDLK_a:
                                action.stop_left = true;
                                protocol.send_action(action);
                                break;
                            case SDLK_d:
                                action.stop_right = true;
                                protocol.send_action(action);
                                break;
                            case SDLK_SPACE:
                                action.stop_jump = true;
                                protocol.send_action(action);
                                break;
                            case SDLK_f:
                                action.unpress_action_button = true;
                                //protocol.send_action(action);
                                break;
                            default:
                                break;
                        }
                        protocol.send_action(action);
                    } else if (e.type == SDL_KEYDOWN) {
                      
                        if (last_event.type == SDL_KEYDOWN &&
                            last_event.key.keysym.sym == e.key.keysym.sym) {
                            continue;
                        }
                                                
                        last_event = e;

                        action_t action;
                        switch (e.key.keysym.sym) {
                            case SDLK_a:
                                action.left = true;
                                //protocol.send_action(action);
                                break;
                            case SDLK_d:
                                action.right = true;
                                //protocol.send_action(action);
                                break;
                            case SDLK_SPACE:
                                action.jump = true;
                                //protocol.send_action(action);
                                break;
                            case SDLK_f:
                                action.press_action_button = true;
                                //protocol.send_action(action);
                                break;
                            default:
                                break;
                        }
                        protocol.send_action(action);
                    }
                    
                }
            usleep(SLEEP_TIME_SENDER);
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
