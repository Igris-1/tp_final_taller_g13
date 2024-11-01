#include "client.h"
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
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

using namespace SDL2pp;

Client::Client(const char* host, const char* port):
        protocol(Socket(host, port)),
        receiver_queue(){
            run();
        }

Client::~Client(){}

void Client::run(){
    try {
        SDL sdl(SDL_INIT_VIDEO);
        Window window("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

        Texture backgroundTexture(renderer, "../client_src/game.png");
        Texture duckTexture2(renderer, "../client_src/duck_sprites.png");

        int bgWidth, bgHeight;
        SDL_QueryTexture(backgroundTexture.Get(), nullptr, nullptr, &bgWidth, &bgHeight);
        float bgAspectRatio = static_cast<float>(bgWidth) / static_cast<float>(bgHeight);
        int bgScaledWidth = SCREEN_WIDTH;
        int bgScaledHeight = static_cast<int>(SCREEN_WIDTH / bgAspectRatio);
        bgScaledWidth = static_cast<int>(SCREEN_HEIGHT * bgAspectRatio);

        bool quit = false;

         Receiver receiver(protocol, receiver_queue);
        Sender sender(protocol);
        std::vector<int> j;
        std::vector<int> x;
        std::vector<int> dir;
        while(sender.is_alive() && receiver.is_alive()){
            game_snapshot_t gs;
            
            if (receiver_queue.try_pop(gs)){

                renderer.Clear();
                renderer.Copy(backgroundTexture, SDL_Rect{0, 0, bgWidth, bgHeight}, SDL_Rect{0, 0, bgScaledWidth, bgScaledHeight});
                //std::cout << "Ducks: " << gs.ducks.size() << std::endl;
                if (j.size() != gs.ducks.size()){
                    j.resize(gs.ducks.size());
                    x.resize(gs.ducks.size());
                    dir.resize(gs.ducks.size());
                }
                for (int i=0; i < gs.ducks.size(); i++) {
                    if (x[i] > gs.ducks[i].x){
                        dir[i] = 1;
                    } else if (x[i] < gs.ducks[i].x){
                        dir[i] = 0;
                    } else {
                        j[i]=0;
                    }
                    x[i] = gs.ducks[i].x,
                    renderer.Copy(duckTexture2, SDL_Rect{j[i]*32+1, 8, 32, 32}, SDL_Rect{x[i], 370, 64, 64}, 0, NullOpt, dir[i]);

                    if (j[i] < 5){
                        j[i]++;
                    } else {
                        j[i] = 1;
                    }
                }
                
                   
                
                renderer.Present();
            }
        }
        protocol.shutDown();
    
        receiver.stop();

        receiver.join();

        sender.stop();
        sender.join();
    } catch (const Exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }

    return;
}