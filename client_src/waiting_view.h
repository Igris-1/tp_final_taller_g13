#ifndef WAITING_VIEW_H
#define WAITING_VIEW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2pp/Chunk.hh>
#include <SDL2pp/Exception.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Window.hh>

using namespace SDL2pp;

class WaitingView {
private:
    SDL sdl;
    Window window;
    Renderer renderer;
    void show_loading_screen();

public:
    WaitingView();
    void hide();
    ~WaitingView();
};



#endif