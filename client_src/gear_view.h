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
    std::vector<Texture>& accessories_textures;
    std::vector<int> gear_frames;
    std::vector<int> gear_vertical_frames;
    std::vector<int> accessories_frames;
    std::vector<int> accessories_vertical_frames;

    void push_gear_frame();
    void push_gear_vertical_frame();
    void draw_accessories(duck_DTO duck, bool facing_direction, int inclination, int x, int y,
                          std::vector<int>* a_f);
    void draw_gear_in_hands(int x, int y, int gear, int inclination, int facing_direction);

public:
    GearView(Renderer& renderer, std::vector<Texture>& gear_textures,
             std::vector<Texture>& accessories_textures);
    void draw_held_gear(bool& facing_direction, duck_DTO& duck, int inclination, int x_sum_value,
                        int y_sum_value);
    void draw_gear(weapon_DTO& weapon);
    ~GearView();
};

#endif