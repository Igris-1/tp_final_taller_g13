#ifndef SENDER_H
#define SENDER_H

#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <map>

#include "protocol_client.h"
#include <unistd.h>
#define SLEEP_TIME_SENDER 2000
#define PLAYER_1 0
#define PLAYER_2 1

class Sender: public Thread {
    private:
        ProtocolClient& protocol;
        SDL_Event last_event;
        int localPlayers;

        // Esta función maneja las acciones de cada jugador según la tecla y el tipo de evento
        void map_key_to_action_1(const SDL_Event& e, action_t& action) {
            action.player_id = PLAYER_1;

            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    // Player 1 controls (w,a,s,d)
                    case SDLK_a:
                        action.left = true;
                        break;
                    case SDLK_d:
                        action.right = true;
                        break;
                    case SDLK_SPACE:
                        action.jump = true;
                        break;
                    case SDLK_f:
                        action.press_action_button = true;
                        break;
                    case SDLK_g:
                        action.press_pick_up_button = true;
                        break;
                    default:
                        break;
                }
            } else if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                    // Player 1 controls
                    case SDLK_a:
                        action.stop_left = true;
                        break;
                    case SDLK_d:
                        action.stop_right = true;
                        break;
                    case SDLK_SPACE:
                        action.stop_jump = true;
                        break;
                    case SDLK_f:
                        action.unpress_action_button = true;
                        break;
                    case SDLK_g:
                        action.unpress_pick_up_button = true;
                        break;
                    default:
                        break;
                }
            }
        }

        void map_key_to_action_2(const SDL_Event& e, action_t& action) {
            action.player_id = PLAYER_2;

            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    // Player 2 controls
                    case SDLK_LEFT:
                        action.left = true;
                        break;
                    case SDLK_RIGHT:
                        action.right = true;
                        break;
                    case SDLK_RCTRL:
                        action.jump = true;
                        break;
                    case SDLK_RSHIFT:
                        action.press_action_button = true;
                        break;
                    case SDLK_l:
                        action.press_pick_up_button = true;
                        break;
                    default:
                        break;

                }
            } else if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                    // Player 2 controls
                    case SDLK_LEFT:
                        action.stop_left = true;
                        break;
                    case SDLK_RIGHT:
                        action.stop_right = true;
                        break;
                    case SDLK_RCTRL:
                        action.stop_jump = true;
                        break;
                    case SDLK_RSHIFT:
                        action.unpress_action_button = true;
                        break;
                    case SDLK_l:
                        action.unpress_pick_up_button = true;
                        break;
                    default:
                        break;
                }
            }
        }

        void run() override {
            try {
                protocol.send_number_of_players(localPlayers);
            
                std::map<SDL_Keycode, int> key_player = {
                    {SDLK_a, PLAYER_1},
                    {SDLK_d, PLAYER_1},
                    {SDLK_SPACE, PLAYER_1},
                    {SDLK_f, PLAYER_1},
                    {SDLK_g, PLAYER_1},
                    {SDLK_LEFT, PLAYER_2},
                    {SDLK_RIGHT, PLAYER_2},
                    {SDLK_RCTRL, PLAYER_2},
                    {SDLK_RSHIFT, PLAYER_2},
                    {SDLK_l, PLAYER_2}
                };
                
                bool quit = false;
                SDL_Event e;
                last_event.type = 0;

                while (!quit && !protocol.socket_closed() && _keep_running) {
                    if (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            quit = true;
                        } else if (e.type == SDL_KEYUP || e.type == SDL_KEYDOWN) {
                            // Evitar el procesamiento de un evento si ya está registrado como el último evento
                            if (e.type == SDL_KEYDOWN && last_event.type == SDL_KEYDOWN &&
                                last_event.key.keysym.sym == e.key.keysym.sym) {
                                continue;
                            }
                            
                            last_event = e;

                            // Procesamos las acciones del player 0 o 1
                            action_t action;
                            if (key_player.find(e.key.keysym.sym) != key_player.end()) {
                                if (key_player[e.key.keysym.sym] == PLAYER_1) {
                                    map_key_to_action_1(e, action);
                                } else {
                                    map_key_to_action_2(e, action);
                                }
                                protocol.send_action(action);
                            }
                        }
                    usleep(SLEEP_TIME_SENDER);
                    }
                }
            } catch (const ClosedQueue& e) {
                stop();
            } catch (const std::exception& e) {
                std::cerr << "Exception while in client sender thread: " << e.what() << std::endl;
            }
        }

    public:
        Sender(ProtocolClient& protocol, int localPlayers): protocol(protocol), localPlayers(localPlayers) {
            start();
        }

        ~Sender() override { 
            _is_alive = false;
        }
};

#endif  // SENDER_H
