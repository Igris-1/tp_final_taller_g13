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
            {SDLK_a, PLAYER_1},     {SDLK_d, PLAYER_1}, {SDLK_SPACE, PLAYER_1},
            {SDLK_f, PLAYER_1},     {SDLK_g, PLAYER_1}, {SDLK_e, PLAYER_1},
            {SDLK_s, PLAYER_1},     {SDLK_w, PLAYER_1}, {SDLK_LEFT, PLAYER_2},
            {SDLK_RIGHT, PLAYER_2}, {SDLK_o, PLAYER_2}, {SDLK_p, PLAYER_2},
            {SDLK_i, PLAYER_2},     {SDLK_k, PLAYER_2}, {SDLK_DOWN, PLAYER_2},
            {SDLK_UP, PLAYER_2}};

    void map_key_to_action_1(const SDL_Event& e, action_t& action);

    void map_key_to_action_2(const SDL_Event& e, action_t& action);

    void run() override;


public:
    Sender(ProtocolClient& protocol, int localPlayers):
            protocol(protocol), localPlayers(localPlayers) {
        start();
    }

    void send_game_to_join(int game_id);

    void send_max_players(int max_players_for_game);

    void send_map_name(std::string& map_name);

    void send_players();

    ~Sender() override;
};

#endif  // SENDER_H
