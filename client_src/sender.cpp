#include "sender.h"
#include "protocol_client.h"


// Esta función maneja las acciones de cada jugador según la tecla y el tipo de evento
void Sender::map_key_to_action_1(const SDL_Event& e, action_t& action) {
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
            case SDLK_e:
                action.press_throw_button = true;
                break;
            case SDLK_s:
                action.press_crouch_button = true;
                break;
            case SDLK_w:
                action.press_look_up_button = true;
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
            case SDLK_s:
                action.unpress_crouch_button = true;
                break;
            case SDLK_w:
                action.unpress_look_up_button = true;
                break;
            default:
                break;
        }
    }
}

void Sender::map_key_to_action_2(const SDL_Event& e, action_t& action) {
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
            case SDLK_k:
                action.press_throw_button = true;
                break;
            case SDLK_DOWN:
                action.press_crouch_button = true;
                break;
            case SDLK_UP:
                action.press_look_up_button = true;
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
            case SDLK_DOWN:
                action.unpress_crouch_button = true;
                break;
            case SDLK_UP:
                action.unpress_look_up_button = true;
                break;
            default:
                break;
        }
    }
}

void Sender::run() {
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

void Sender::send_game_to_join(int game_id) {
    // int game_id = std::stoi(input);
    protocol.send_number(game_id);
}

void Sender::send_max_players(int max_players_for_game){
    protocol.send_number(max_players_for_game);
}

void Sender::send_map_name(std::string& map_name){
    protocol.send_string(map_name);
}

void Sender::send_players() { protocol.send_number(localPlayers); }

Sender::~Sender() {}