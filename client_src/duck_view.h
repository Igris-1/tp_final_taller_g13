#ifndef DUCK_VIEW_H
#define DUCK_VIEW_H

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/Exception.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Window.hh>
#include <map>

#include "../common_src/game_snapshot_t.h"


using namespace SDL2pp;

class DuckView {
private:
    bool facing_direction;
    std::map<int, SDL_Point> walk_frames;
    int walk_frame;
    std::map<int, SDL_Point> flying_frames;
    int flying_frame;
    Renderer& renderer;
    Texture& duck_texture;
    Texture& wing_texture;
    std::vector<Texture>& weapon_textures;

    void draw_dead_duck(duck_DTO& duck);
    void draw_jumping_duck(duck_DTO& duck, Texture* weapon_texture);
    void draw_falling_duck(duck_DTO& duck, Texture* weapon_texture);
    void draw_moving_duck(duck_DTO& duck, Texture* weapon_texture);
    void draw_idle_duck(duck_DTO& duck, Texture* weapon_texture);

public:
    DuckView(Renderer& renderer, Texture& duck_sprites, Texture& wing_sprites,
             std::vector<Texture>& weapon_sprites);
    void draw_duck(duck_DTO& duck);

    ~DuckView();
};

#endif
