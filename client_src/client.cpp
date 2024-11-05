#include "client.h"
#include <iostream>
#include <vector>
#include "../common_src/action_t.h"
#include "../common_src/game_snapshot_t.h"
#include "../common_src/queue.h"

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
        SDL sdl(SDL_INIT_VIDEO);
        Window window("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);


        Surface s = Surface("../client_src/duck_sprites.png");

        Texture backgroundTexture(renderer, "../client_src/game.png");
        Texture duckTexture(renderer, s);
        Texture wingTexture(renderer, "../client_src/alas.png");

        int bgWidth, bgHeight;
        SDL_QueryTexture(backgroundTexture.Get(), nullptr, nullptr, &bgWidth, &bgHeight);
        float bgAspectRatio = static_cast<float>(bgWidth) / static_cast<float>(bgHeight);
        int bgScaledWidth = SCREEN_WIDTH;
        int bgScaledHeight = static_cast<int>(SCREEN_WIDTH / bgAspectRatio);
        bgScaledWidth = static_cast<int>(SCREEN_HEIGHT * bgAspectRatio);

        bool quit = false;

        Receiver receiver(protocol, receiver_queue);
        Sender sender(protocol);
        std::vector<int> j(0);
        std::vector<int> ja(0);
        std::vector<int> dir(0);
        while(sender.is_alive() && receiver.is_alive()){
            game_snapshot_t gs;
            
            if (receiver_queue.try_pop(gs)){

                renderer.Clear();
                renderer.Copy(backgroundTexture, SDL_Rect{0, 0, bgWidth, bgHeight}, SDL_Rect{0, 0, bgScaledWidth, bgScaledHeight});
                if (j.size() != gs.ducks.size()){
                    j.resize(gs.ducks.size(),1);
                    ja.resize(gs.ducks.size(),2);
                    dir.resize(gs.ducks.size(),0);
                }
                for (int i=0; i < gs.ducks.size(); i++) {
                    if (gs.ducks[i].is_moving_right){
                        dir[i] = 0;
                    } else if (gs.ducks[i].is_moving_left){
                        dir[i] = 1;
                    }
                    if (gs.ducks[i].jumping){
                        renderer.Copy(duckTexture, SDL_Rect{1*32+1, 44, 32, 32}, SDL_Rect{gs.ducks[i].x-16, gs.ducks[i].y, 64, 64}, 0, NullOpt, dir[i]);
                    } else if (gs.ducks[i].falling){
                        int ai = 10;
                        if (dir[i]){
                            ai = 22;
                        }
                        renderer.Copy(duckTexture, SDL_Rect{3*32+1, 44, 32, 32}, SDL_Rect{gs.ducks[i].x-16, gs.ducks[i].y, 64, 64}, 0, NullOpt, dir[i]);
                        renderer.Copy(wingTexture, SDL_Rect{ja[i]*16, 32, 16, 16}, SDL_Rect{gs.ducks[i].x-16+ai, gs.ducks[i].y+15, 32, 32}, 0, NullOpt, dir[i]);
                    } else if (gs.ducks[i].is_moving_right || gs.ducks[i].is_moving_left){
                        int ai = 10;
                        if (dir[i]){
                            ai = 22;
                        }
                        renderer.Copy(duckTexture, SDL_Rect{j[i]*32+1, 8, 32, 32}, SDL_Rect{gs.ducks[i].x-16, gs.ducks[i].y, 64, 64}, 0, NullOpt, dir[i]);
                        renderer.Copy(wingTexture, SDL_Rect{16, 0, 16, 16}, SDL_Rect{gs.ducks[i].x-16+ai, gs.ducks[i].y+25, 32, 32}, 0, NullOpt, dir[i]);
                    } else {
                        renderer.Copy(duckTexture, SDL_Rect{1, 8, 32, 32}, SDL_Rect{gs.ducks[i].x-16, gs.ducks[i].y, 64, 64}, 0, NullOpt, dir[i]);
                        int ai = 10;
                        if (dir[i]){
                            ai = 22;
                        }
                        renderer.Copy(wingTexture, SDL_Rect{0, 0, 16, 16}, SDL_Rect{gs.ducks[i].x-16+ai, gs.ducks[i].y+25, 32, 32}, 0, NullOpt, dir[i]);
                    }

                    if (ja[i]<5){
                        ja[i]++;
                    } else {
                        ja[i] = 2;
                    }

                    if (j[i] < 5){
                        j[i]++;
                    } else {
                        j[i] = 1;
                    }
                }
                renderer.Present();
            }
            usleep(1000);
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