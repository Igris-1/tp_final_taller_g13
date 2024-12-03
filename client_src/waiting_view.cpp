#include "waiting_view.h"

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

WaitingView::WaitingView():
    sdl(SDL_INIT_VIDEO),
    window("Waiting room", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
            SCREEN_HEIGHT, SDL_WINDOW_SHOWN),
    renderer(window, 2, SDL_RENDERER_ACCELERATED) {
        show_loading_screen();
    }

void WaitingView::show_loading_screen() {
    Texture loging_image(renderer, "../assets/sprites/loading_screen.png");

    renderer.Copy(loging_image, SDL_Rect{0, 0, 1280, 720},
                  SDL_Rect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});

    //Mix_VolumeMusic(5);
    //Mix_PlayMusic(, -1);

    renderer.Present();
}

void WaitingView::hide() {

    renderer.~Renderer();
    window.~Window();
}

WaitingView::~WaitingView() {}