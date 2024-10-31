#include "client.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Exception.hh>
#include "../common_src/action_t.h"
#include "../common_src/game_snapshot_t.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "protocol_client.h"

#define EXIT_CODE "q"
#define SCREEN_WIDTH 820
#define SCREEN_HEIGHT 500

Client::Client(const char* host, const char* port):
        protocol(Socket(host, port)),
        receiver_queue(){
            run();
        }

Client::~Client(){}

void Client::run(){
    try {
        std::cout << "Press 'q' to quit" << std::endl;
        SDL2pp::SDL sdl(SDL_INIT_VIDEO);
        SDL2pp::Window window("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

        SDL2pp::Texture backgroundTexture(renderer, "../client_src/game.png");
        SDL2pp::Texture duckTexture(renderer, "../client_src/duck.png");

        int bgWidth, bgHeight;
        SDL_QueryTexture(backgroundTexture.Get(), nullptr, nullptr, &bgWidth, &bgHeight);
        float bgAspectRatio = static_cast<float>(bgWidth) / static_cast<float>(bgHeight);
        int bgScaledWidth = SCREEN_WIDTH;
        int bgScaledHeight = static_cast<int>(SCREEN_WIDTH / bgAspectRatio);
        bgScaledWidth = static_cast<int>(SCREEN_HEIGHT * bgAspectRatio);

        int duckWidth, duckHeight;
        SDL_QueryTexture(duckTexture.Get(), nullptr, nullptr, &duckWidth, &duckHeight);
        float duckAspectRatio = static_cast<float>(duckWidth) / static_cast<float>(duckHeight);
        int duckScaledWidth = 64;
        int duckScaledHeight = static_cast<int>(duckScaledWidth / duckAspectRatio);

        bool quit = false;
        SDL_Event e;

        SDL_Rect duckRect;

        Sender sender(protocol);
        Receiver receiver(protocol, receiver_queue);

        while(sender.is_alive() && receiver.is_alive()){
            game_snapshot_t gs;
            if(receiver_queue.try_pop(gs)){
                if (gs.ducks_len > 0) {
                    int x = static_cast<int>(gs.ducks[0].x);
                    std::cout << "Duck at (" << x << ", 0)" << std::endl;
                    duckRect = { x, 370, duckScaledWidth, duckScaledHeight };
                }
            }
            
        
            renderer.Clear();
            renderer.Copy(backgroundTexture, SDL_Rect{0, 0, bgWidth, bgHeight}, SDL_Rect{0, 0, bgScaledWidth, bgScaledHeight});
            renderer.Copy(duckTexture, SDL_Rect{0, 0, duckWidth, duckHeight}, duckRect);
            renderer.Present();
        }
        protocol.shutDown();
    
        receiver.stop();

        receiver.join();

        sender.stop();
        sender.join();
    } catch (const SDL2pp::Exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }

    return;
}