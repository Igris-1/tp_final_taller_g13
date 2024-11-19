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
    ProtocolClient protocol;
    Queue<Message> receiver_queue;

    game_snapshot_t get_snapshot();
    GameView game_view;

public:
    void run();
    Client(const char* host, const char* port);
    void setLocalPlayers(int players);
    void select_game_mode(int gmae_mode);
    std::vector<int> get_available_games();

    ~Client();
};

#endif