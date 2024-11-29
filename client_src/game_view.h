#ifndef GAME_VIEW_H
#define GAME_VIEW_H

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

#include "../common_src/action_t.h"
#include "../common_src/game_snapshot_t.h"

#include "duck_view.h"
#include "gear_view.h"

using namespace SDL2pp;


class GameView {
private:
    map_structure_t map;
    SDL sdl;
    Window window;
    Renderer renderer;
    std::vector<Texture> background_sprites;
    std::vector<Texture> platform_sprites;
    std::vector<Texture> duck_sprites;
    std::vector<Texture> wing_sprites;
    std::vector<Texture> gear_sprites;
    std::vector<Texture> bullet_sprites;
    std::vector<Texture> scoreboard_font;
    std::vector<Texture> box_sprites;
    std::vector<Texture> accessories_sprites;
    std::vector<Texture> duck_looking_up_sprites;
    std::vector<Texture> dead_duck_sprites;

    std::vector<DuckView> duck_views;
    GearView gear_view;

    void set_up_game();
    void render_map();
    void render_ducks(game_snapshot_t gs);
    void render_bullets(game_snapshot_t gs);
    void render_weapons(game_snapshot_t gs);
    void render_scoreboard(score_DTO score);
    void zoom(game_snapshot_t gs);
    void render_boxes(game_snapshot_t gs);
    void add_ducks(game_snapshot_t gs);
    void load_duck_textures();
    void load_music();
    void load_gear_textures();
    void load_map_textures();
    void show_loading_screen();

public:
    GameView();
    void add_map(map_structure_t map);
    void render_score(score_DTO score);
    void render_endgame_score(score_DTO score);
    void render_game(game_snapshot_t gs);
    ~GameView();
};

#endif