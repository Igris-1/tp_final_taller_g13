#ifndef CLIENT_H
#define CLIENT_H

#include <cstdint>
#include <string>
#include "../common_src/socket.h"
#include "protocol_client.h"
#include "receiver.h"
#include "sender.h"
#include "../common_src/thread.h"
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Exception.hh>

using namespace SDL2pp;

class Client: public Thread {
private:
    ProtocolClient protocol;
    Queue<game_snapshot_t> receiver_queue;

    void command (char pressed_key);
    game_snapshot_t get_snapshot();
    

public:
    void run();
    Client(const char* host, const char* port);
    void change_color(Surface& surface, SDL_Color targetColor, SDL_Color newColor);
    ~Client();
};

#endif
