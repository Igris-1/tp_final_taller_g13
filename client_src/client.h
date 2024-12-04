#ifndef CLIENT_H
#define CLIENT_H

#include <cstdint>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/Exception.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Window.hh>

#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "game_view.h"
#include "message.h"
#include "protocol_client.h"
#include "receiver.h"
#include "sender.h"

#define MAX_PLAYERS 2
#define PLAYER_1 0
#define PLAYER_2 1

using namespace SDL2pp;

class Client {
private:
    int localPlayers;
    int max_players_for_game;
    uint8_t game_to_join;
    ProtocolClient protocol;
    Queue<Message> receiver_queue;
    Queue<action_t> sender_queue;
    bool event_queue_blocked;
    SDL_Event last_event;
    std::map<SDL_Keycode, int> key_player = {
            {SDLK_a, PLAYER_1},     {SDLK_d, PLAYER_1}, {SDLK_SPACE, PLAYER_1},
            {SDLK_f, PLAYER_1},     {SDLK_g, PLAYER_1}, {SDLK_e, PLAYER_1},
            {SDLK_s, PLAYER_1},     {SDLK_w, PLAYER_1}, {SDLK_LEFT, PLAYER_2},
            {SDLK_RIGHT, PLAYER_2}, {SDLK_o, PLAYER_2}, {SDLK_p, PLAYER_2},
            {SDLK_i, PLAYER_2},     {SDLK_k, PLAYER_2}, {SDLK_DOWN, PLAYER_2},
            {SDLK_UP, PLAYER_2}};

    void map_key_to_action_1(const SDL_Event& e, action_t& action);

    void map_key_to_action_2(const SDL_Event& e, action_t& action);

    game_snapshot_t get_snapshot();
    GameView game_view;
    std::vector<games_DTO> games;
    std::string map_name = "";
    std::map<int, std::function<void(Message& m, Sender& sender)>> actions;

    void set_client();
    bool sdl_pop();

public:
    void run();
    Client(const char* host, const char* port, uint8_t game_id);
    
    void setLocalPlayers(int players);
    void setMaxPlayers(int max_players);
    void setMapName(const std::string& map_name);
    void select_game_mode(int game_mode);
    // std::vector<int> get_available_games();
    void select_game(int game_id);
    std::vector<games_DTO> get_games_info();

    ~Client();
};

#endif