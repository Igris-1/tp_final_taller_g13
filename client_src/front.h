/*#ifndef FRONT_H_
#define FRONT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Exception.hh>
#include <iostream>
#include "../common_src/queue.h"
#include "receiver.h"
#include "sender.h"
#include "protocol_client.h"

const int SCREEN_WIDTH = 820;
const int SCREEN_HEIGHT = 500;

//using namespace SDL2pp;
class Front {
    private:
        ProtocolClient protocol;
        Receiver receiver;
        Sender sender;
        Queue<game_snapshot_t> receiver_queue;
 
    public:

        Front(ProtocolClient&& protocol):
        protocol(Socket(host, port)),
        receiver_queue(),
        receiver(protocol, receiver_queue),
        sender(protocol) {
            start();
        }

        ~Front() {
            protocol.shutDown();
            
            receiver.stop();
            sender.stop();

            receiver.join();
            sender.join();
        }

        void start(){
            try {

                SDL2pp::SDL sdl(SDL_INIT_VIDEO);
                SDL2pp::Window window("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
                SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

                SDL2pp::Texture backgroundTexture(renderer, "game.png");
                SDL2pp::Texture duckTexture(renderer, "duck.png");

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

                SDL_Rect duckRect = { 300, 370, duckScaledWidth, duckScaledHeight };


                while(true){
                    game_snapshot_t gs;
                    receiver_queue.try_pop(gs);
                    int x = static_cast<int>(gs.ducks[0].x);
                    duckRect.x += x*20;
                

                    renderer.Clear();
                    renderer.Copy(backgroundTexture, SDL_Rect{0, 0, bgWidth, bgHeight}, SDL_Rect{0, 0, bgScaledWidth, bgScaledHeight});
                    renderer.Copy(duckTexture, SDL_Rect{0, 0, duckWidth, duckHeight}, duckRect);
                    renderer.Present();
                }

            } catch (const SDL2pp::Exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return;
            }

            return;
        }
    };
#endif  // FRONT_H_*/