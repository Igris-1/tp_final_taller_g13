#ifndef CLIENT_H
#define CLIENT_H

#include <cstdint>
#include <string>

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
#include "protocol_client.h"
#include "receiver.h"
#include "sender.h"
#include "message.h"
#include <vector>

using namespace SDL2pp;

class Client{
private:
    int localPlayers;
    uint8_t game_to_join;
    ProtocolClient protocol;
    Queue<Message> receiver_queue;

    game_snapshot_t get_snapshot();
    GameView game_view;
    std::vector <games_DTO> games;

public:
    void run();
    Client(const char* host, const char* port, uint8_t game_id);
    void setLocalPlayers(int players);
    void select_game_mode(int game_mode);
    // std::vector<int> get_available_games();
    void select_game(int game_id);
    std::vector<games_DTO> get_games_info();

    ~Client();
};

#endif