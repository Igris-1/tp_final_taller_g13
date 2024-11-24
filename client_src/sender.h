#ifndef SENDER_H
#define SENDER_H

#include <iostream>
#include <map>

#include <SDL2/SDL.h>
#include <unistd.h>

#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "protocol_client.h"

#define SLEEP_TIME_SENDER 2000
#define PLAYER_1 0
#define PLAYER_2 1

class Sender: public Thread {
private:
    ProtocolClient& protocol;
    SDL_Event last_event;
    int localPlayers = 2;
    std::map<SDL_Keycode, int> key_player = {
            {SDLK_a, PLAYER_1}, {SDLK_d, PLAYER_1},    {SDLK_SPACE, PLAYER_1}, {SDLK_f, PLAYER_1},
            {SDLK_g, PLAYER_1}, {SDLK_LEFT, PLAYER_2}, {SDLK_RIGHT, PLAYER_2}, {SDLK_o, PLAYER_2},
            {SDLK_p, PLAYER_2}, {SDLK_i, PLAYER_2}};

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
                case SDLK_o:
                    action.jump = true;
                    break;
                case SDLK_p:
                    action.press_action_button = true;
                    break;
                case SDLK_i:
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
                case SDLK_o:
                    action.stop_jump = true;
                    break;
                case SDLK_p:
                    action.unpress_action_button = true;
                    break;
                case SDLK_i:
                    action.unpress_pick_up_button = true;
                    break;
                default:
                    break;
            }
        }
    }

    void run() override {
        try {
            bool quit = false;
            SDL_Event e;

            while (!quit && !protocol.socket_closed() && _keep_running) {
                // Procesar eventos
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                        break;
                    } else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
                        if (e.type == last_event.type &&
                            e.key.keysym.sym == last_event.key.keysym.sym) {
                            // Evita procesar eventos repetidos
                            continue;
                        }

                        last_event = e;

                        // Determinar el jugador y la acción
                        action_t action;
                        if (key_player.count(e.key.keysym.sym) > 0) {
                            if (key_player[e.key.keysym.sym] == PLAYER_1) {
                                map_key_to_action_1(e, action);
                            } else if (key_player[e.key.keysym.sym] == PLAYER_2 &&
                                       localPlayers == 2) {
                                map_key_to_action_2(e, action);
                            }
                            protocol.send_action(action);
                        }
                    }
                }

                SDL_Delay(1);
            }
        } catch (const ClosedQueue& e) {
            stop();
        } catch (const std::exception& e) {
            std::cerr << "Exception while in client sender thread: " << e.what() << std::endl;
        }
    }


public:
    Sender(ProtocolClient& protocol, int localPlayers):
            protocol(protocol), localPlayers(localPlayers) {
        start();
    }

    void send_game_to_join(int game_id) {
        // int game_id = std::stoi(input);
        protocol.send_number(game_id);
    }

    void send_players() { protocol.send_number(localPlayers); }

    ~Sender() override { _is_alive = false; }
};

#endif  // SENDER_H
