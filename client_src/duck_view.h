#ifndef DUCK_VIEW_H
#define DUCK_VIEW_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Exception.hh>
#include <vector>
#include "../common_src/game_snapshot_t.h"


using namespace SDL2pp;

class DuckView{
    private:
        bool facing_direction;
        int walk_animation_frame;
        int wing_flying_animation_frame;
        Renderer& renderer;
        Texture& duck_texture;
        Texture& wing_texture;
        std::vector<Texture>& weapon_textures;

    public:
        DuckView(Renderer& renderer, Texture& duck_sprites, Texture& wing_sprites, std::vector<Texture>& weapon_sprites);
        void draw_duck(duck_DTO& duck);
        void draw_dead_duck();
        void draw_jumping_duck();
        void draw_falling_duck();
        void draw_moving_duck();
        ~DuckView();
};

#endif
