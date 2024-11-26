#ifndef GEAR_VIEW_H
#define GEAR_VIEW_H

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

#include "../common_src/duck_DTO.h"

using namespace SDL2pp;

class GearView {

private:
    Renderer& renderer;
    std::vector<Texture>& gear_textures;
    std::vector<Texture>& accessories_sprites;
    std::vector<std::vector<int>> gear_frames;
    void push_gear_frame_values();
    void push_gear_frame_for_idle_walking_duck();
    void push_gear_frame_for_jumping_falling_duck();
    void push_gear_frame_for_flying_duck();
    void push_gear_frame_for_crouching_duck();
    void draw_accessories(duck_DTO duck, bool facing_direction, int gear_id, int action);

public:
    GearView(Renderer& renderer, std::vector<Texture>& gear_textures, std::vector<Texture>& accessories_sprites);
    void draw_held_gear(bool& facing_direction, duck_DTO& duck);
    void draw_gear(weapon_DTO& weapon);
    
    ~GearView();
};

#endif  