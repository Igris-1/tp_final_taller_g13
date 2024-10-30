#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Exception.hh>
#include <iostream>
#include "../common_src/queue.h"

extern Queue<SDL_Event> eventQueue;

const int SCREEN_WIDTH = 820;
const int SCREEN_HEIGHT = 500;
const int MY_CUSTOM_EVENT_TYPE = SDL_RegisterEvents(1); // Registrar evento personalizado

struct MyCustomEvent {
    int x;
};

int main(int argc, char* args[]) {
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

        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_d) {
                        duckRect.x += 20;
                    } else if (e.key.keysym.sym == SDLK_a) {
                        duckRect.x -= 20;
                    }
                }/* else if (e.type == MY_CUSTOM_EVENT_TYPE) {
                    MyCustomEvent* myData = reinterpret_cast<MyCustomEvent*>(&e.user.data1);
                    duckRect.x = 300 + myData->x; 
                }*/
            }

            renderer.Clear();
            renderer.Copy(backgroundTexture, SDL_Rect{0, 0, bgWidth, bgHeight}, SDL_Rect{0, 0, bgScaledWidth, bgScaledHeight});
            renderer.Copy(duckTexture, SDL_Rect{0, 0, duckWidth, duckHeight}, duckRect);
            renderer.Present();
        }

    } catch (const SDL2pp::Exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
