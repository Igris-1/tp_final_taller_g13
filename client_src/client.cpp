#include "client.h"

#include <iostream>
#include <vector>

#include "../common_src/action_t.h"
#include "../common_src/game_snapshot_t.h"
#include "../common_src/queue.h"

#define LOCAL_PLAYERS 2
#define LOOP_TIME 2000

Client::Client(const char* host, const char* port, uint8_t game_id):
        localPlayers(LOCAL_PLAYERS), protocol(Socket(host, port)), receiver_queue(), game_view(), sender_queue(),
        event_queue_blocked(false), max_players_for_game(MAX_PLAYERS) {
    game_to_join = game_id;
    set_client();
}

void Client::set_client(){
    actions = {
        {MAP_CODE, [&](Message& m, Sender& sender) {
            map_structure_t map = m.get_map();
            game_view.add_map(map);
            
        }},
        {GAME_SNAPSHOT_CODE, [&](Message& m, Sender& sender) {
            event_queue_blocked = false;
            game_snapshot_t gs = m.get_game_snapshot();
            game_view.render_game(gs);
        }},
        {SCORE_CODE, [&](Message& m, Sender& sender) {
            event_queue_blocked = true;    
            score_DTO score = m.get_score();
            game_view.render_score(score); 
        }},
        {END_SCORE_CODE, [&](Message& m, Sender& sender) {    
            score_DTO score = m.get_score();
            game_view.render_endgame_score(score);
        }},
        {GAMES_INFO_CODE, [&](Message& m, Sender& sender) {   
            std::string input;
            std::getline(std::cin, input);
        }},
        {PLAYERS_CODE, [&](Message& m, Sender& sender) {  
            sender.send_players();
        }},
        {SEND_GAME_PLAYERS, [&](Message& m, Sender& sender) { 
            sender.send_players();
            sender.send_game_to_join(game_to_join);
        }},
        {SEND_MAX_PLAYERS, [&](Message& m, Sender& sender) {  
            sender.send_max_players(max_players_for_game);
        }},
        {SEND_MAP_NAME, [&](Message& m, Sender& sender) {  
            sender.send_map_name(this->map_name);
        }}
    };
}

void Client::setLocalPlayers(int players) { localPlayers = players; }

void Client::setMaxPlayers(int max_players) { max_players_for_game = max_players; }

Client::~Client() {}

void Client::select_game_mode(int game_mode) { protocol.send_number(game_mode); }

// std::vector<int> Client::get_available_games() {
// for refhresh button
// }

void Client::setMapName(const std::string& map_name){
    this->map_name = map_name;
}

void Client::select_game(int game_id) { protocol.send_number(game_id); }

std::vector<games_DTO> Client::get_games_info() { return this->games; }

// Esta función maneja las acciones de cada jugador según la tecla y el tipo de evento
void Client::map_key_to_action_1(const SDL_Event& e, action_t& action) {
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

void Client::map_key_to_action_2(const SDL_Event& e, action_t& action) {
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


bool Client::sdl_pop(){
    bool quit = false;
    SDL_Event e = {0};
    last_event = {0};

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
            break;
        }else if (!e.type == SDL_KEYDOWN && event_queue_blocked) {
            continue;
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
                sender_queue.push(action);
            }
        }
    }
    return quit;
}

void Client::run() {

    try {
        Receiver receiver(protocol, receiver_queue);
        Sender sender(protocol, localPlayers, sender_queue);

        bool player_wants_to_quit = false;
        
        while (!player_wants_to_quit && sender.is_alive() && receiver.is_alive()) {
            auto start_time = std::chrono::steady_clock::now();
            Message m(0);
            if (receiver_queue.try_pop(m)) {
                if (actions.count(m.get_code())) {
                    actions[m.get_code()](m, sender);
                } else {
                    std::cerr << "Código desconocido: " << m.get_code() << std::endl;
                }
            }
            player_wants_to_quit = sdl_pop();
            auto end_time = std::chrono::steady_clock::now();
            auto elapsed_time =
                std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time)
                        .count();
            int remaining_time = LOOP_TIME - elapsed_time;
            std::this_thread::sleep_for(std::chrono::microseconds(remaining_time));
        }
        protocol.shutDown();

        receiver.stop();
        receiver.join();

        sender_queue.close();
        sender.stop();
        sender.join();

    } catch (const Exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }
}